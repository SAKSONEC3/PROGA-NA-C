#ifndef SED_H
#define SED_H

typedef struct {
    char mode;
    char* old;
    char* new;
} Command;

Command* parse_args(int argc, char* argv[]);

#endif
