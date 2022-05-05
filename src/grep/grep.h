#ifndef SRC_GREP_H_
#define SRC_GREP_H_

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 4096

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
void grep(flags f, FILE *file, char *filename, int idx);

#endif  // SRC_GREP_H_
