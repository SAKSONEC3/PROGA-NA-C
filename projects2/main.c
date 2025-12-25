#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sed.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Use: %s file 'cmd'\n", argv[0]);
        return 1;
    }
    
    Command* cmd = parse_cmd(argv[2]);
    if (!cmd) return 1;
    
    FILE* f = fopen(argv[1], "r+");
    if (!f) return 1;
    
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    char* buf = malloc(sz+1);
    fread(buf, 1, sz, f);
    buf[sz] = 0;
    
    char* new = malloc(sz*2);
    new[0] = 0;
    
    char* line = strtok(buf, "\n");
    while (line) {
        char out[1024];
        run_cmd(cmd, line, out);
        if (out[0]) {
            strcat(new, out);
            strcat(new, "\n");
        }
        line = strtok(NULL, "\n");
    }
    
    fseek(f, 0, SEEK_SET);
    fwrite(new, 1, strlen(new), f);
    ftruncate(fileno(f), strlen(new));
    
    fclose(f);
    free(buf);
    free(new);
    free_cmd(cmd);
    
    return 0;
}
