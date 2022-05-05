#ifndef SRC_GREP_H_
#define SRC_GREP_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    bool e;
    bool i;
    bool v;
    bool c;
    bool l;
    bool n;
    bool h;
    bool s;
    bool f;
    bool o;
} flags;

int get_flags(flags *f, int *opt, int argc, char **argv);
void grep(flags f, FILE *file);

#endif  // SRC_GREP_H_
