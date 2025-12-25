#include "sed.h"
#include <string.h>
#include <stdlib.h>

Command* parse_cmd(const char* cmd_str) {
    Command* cmd = malloc(sizeof(Command));
    
    if (cmd_str[0] == 's' && cmd_str[1] == '/') {
        cmd->type = 's';
        const char* p = cmd_str + 2;
        const char* sep = strchr(p, '/');
        
        char pat[256];
        strncpy(pat, p, sep-p);
        pat[sep-p] = 0;
        regcomp(&cmd->regex, pat, REG_EXTENDED);
        
        p = sep + 1;
        sep = strchr(p, '/');
        cmd->repl = malloc(sep-p+1);
        strncpy(cmd->repl, p, sep-p);
        cmd->repl[sep-p] = 0;
        
    } else if (cmd_str[0] == '/') {
        cmd->type = 'd';
        cmd->repl = NULL;
        
        char pat[256];
        strncpy(pat, cmd_str+1, strlen(cmd_str)-3);
        pat[strlen(cmd_str)-3] = 0;
        regcomp(&cmd->regex, pat, REG_EXTENDED);
    }
    
    return cmd;
}

void run_cmd(Command* cmd, char* line, char* out) {
    regmatch_t m[1];
    
    if (cmd->type == 's') {
        if (regexec(&cmd->regex, line, 1, m, 0) == 0) {
            strncpy(out, line, m[0].rm_so);
            out[m[0].rm_so] = 0;
            strcat(out, cmd->repl);
            strcat(out, line + m[0].rm_eo);
        } else {
            strcpy(out, line);
        }
    } else {
        strcpy(out, regexec(&cmd->regex, line, 1, m, 0) == 0 ? "" : line);
    }
}

void free_cmd(Command* cmd) {
    regfree(&cmd->regex);
    if (cmd->repl) free(cmd->repl);
    free(cmd);
}
