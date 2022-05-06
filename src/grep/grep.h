#ifndef SRC_GREP_H_
#define SRC_GREP_H_

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 4096

struct flags {
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
};

bool match_pattern(struct flags f, const char *str, const char *pattern);
bool get_pattern(const char *argv, const struct flags f, char *ret);
int get_flags(struct flags *f, int *opt, int argc, char **argv);
void grep(const struct flags f, const char *filename, const char *pattern,
          const int file_count);
void print_usage();
void print_no_file(const char *filename);

#endif  // SRC_GREP_H_

// DONE [-e-i-v-s-f]
