#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sed.h"

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;
    
    Command* cmd = parse_args(argc, argv);
    FILE* f = fopen(argv[1], "r+");
    if (!f) return 1;
    
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* content = malloc(size + 1);
    fread(content, 1, size, f);
    content[size] = 0;
    
    char* new = malloc(size * 3);
    new[0] = 0;
    
    char* line = strtok(content, "\n");
    while (line) {
        char out[1024];
        
        if (cmd->mode == 'r') {
            strcpy(out, line);
            char* pos;
            while ((pos = strstr(out, cmd->old))) {
                char temp[1024];
                strncpy(temp, out, pos - out);
                temp[pos - out] = 0;
                strcat(temp, cmd->new);
                strcat(temp, pos + strlen(cmd->old));
                strcpy(out, temp);
            }
        }
        else if (cmd->mode == 'd') {
            if (strstr(line, cmd->old)) out[0] = 0;
            else strcpy(out, line);
        }
        else if (cmd->mode == 'f') {
            sprintf(out, "%s%s", cmd->new, line);
        }
        else if (cmd->mode == 'b') {
            sprintf(out, "%s%s", line, cmd->new);
        }
        
        if (strlen(out) > 0) {
            strcat(new, out);
            strcat(new, "\n");
        }
        
        line = strtok(NULL, "\n");
    }
    
    fseek(f, 0, SEEK_SET);
    fwrite(new, 1, strlen(new), f);
    ftruncate(fileno(f), strlen(new));
    
    fclose(f);
    free(content);
    free(new);
    if (cmd->old) free(cmd->old);
    if (cmd->new) free(cmd->new);
    free(cmd);
    
    return 0;
}
