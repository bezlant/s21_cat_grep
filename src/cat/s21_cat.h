#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

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

bool parse_flag(flags *const f, const char *const str);
bool check_args(const int count, const char **const strs);
bool check_flags(const char *const flags);
void print_file(flags f, FILE *file, int *const cnt);
void handle_string(flags f, const char *const str, const size_t len,
                   int *const cnt, int *const prev);
void handle_b(const char *const str, const size_t len, int *const cnt);
void handle_s(const char *const str, const size_t len, int *const prev);
void handle_n(const char *const str, const size_t len, int *const cnt);
void handle_E(const char *const str, const size_t len);
void handle_T(const char *const str, const size_t len);
void handle_t(const char *const str, const size_t len);
void handle_e(const char *const str, const size_t len);
void num_to_str(int val, char *const num);

#endif  // SRC_CAT_S21_CAT_H_
