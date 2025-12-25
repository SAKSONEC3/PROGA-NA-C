#include "sed.h"
#include <stdlib.h>
#include <string.h>

Command* parse_args(int argc, char* argv[]) {
    Command* cmd = malloc(sizeof(Command));
    
    if (strcmp(argv[2], "-r") == 0) {
        cmd->mode = 'r';
        cmd->old = strdup(argv[3]);
        cmd->new = strdup(argv[4]);
    } 
    else if (strcmp(argv[2], "-d") == 0) {
        cmd->mode = 'd';
        cmd->old = strdup(argv[3]);
        cmd->new = NULL;
    }
    else if (strcmp(argv[2], "-i") == 0) {
        if (strcmp(argv[3], "-f") == 0) {
            cmd->mode = 'f';
            cmd->new = strdup(argv[4]);
            cmd->old = NULL;
        }
        else if (strcmp(argv[3], "-b") == 0) {
            cmd->mode = 'b';
            cmd->new = strdup(argv[4]);
            cmd->old = NULL;
        }
    }
    
    return cmd;
}
