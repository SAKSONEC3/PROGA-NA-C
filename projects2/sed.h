#ifndef SED_H
#define SED_H

#include <regex.h>

typedef struct {
    char type;
    regex_t regex;
    char* repl;
} Command;

Command* parse_cmd(const char* cmd);
void run_cmd(Command* cmd, char* line, char* out);
void free_cmd(Command* cmd);

#endif
