#ifndef SRC_s21_CAT_H_
#define SRC_s21_CAT_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define SIZE 256

enum fl { b, gnu_b, e, gnu_e, n, gnu_n, s, gnu_s, t, gnu_t };

typedef struct flags {
    bool b;
    bool e;
    bool E;
    bool n;
    bool s;
    bool t;
    bool T;
    int count;
} flags;

bool parse_flag(flags *f, const char *flags);
bool check_args(const int count, char **strs);
bool check_flags(const char *flags);
void print_file(flags f, FILE *file, int *cnt);
void handle_string(flags f, char *str, size_t len, int *cnt, int *prev);
void handle_b(char *str, size_t len, int *cnt);
void handle_s(char *str, size_t len, int *prev);
void handle_n(char *str, size_t len, int *cnt);
void handle_E(char *str, size_t len);
void handle_T(const char *str, size_t len);
void handle_t(const char *str, size_t len);
void handle_e(const char *str, size_t len);
void num_to_str(int val, char *num);

#endif  // SRC_s21_CAT_H_
