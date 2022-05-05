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

bool match_pattern(flags f, char *str, char *pattern);
bool get_pattern(char *argv, flags f, char *ret);
int get_flags(flags *f, int *opt, int argc, char **argv);
void grep(flags f, char *filename, char *pattern);
void handle_regexp(flags f, FILE *file, char *filename, char *reg_buff);
void print_usage();
void print_no_file(char *filename);

#endif  // SRC_GREP_H_

// FILE *file = fopen(argv[i], "r");
// if (!file) {
//     if (!f.s && (!f.e || i != 2))
//         print_no_file(argv[i]);
//     if (f.f && i == 2) {
//         print_no_file(argv[i]);
//         break;
//     }
// } else {
//     grep(f, file, pattern);
//     fclose(file);
// }
