#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 4096
/* [TODO] */
/* 1. Parse template correctly after all flags or before */

enum { SUCCESS = 0, NO_FILE = 1, NON_EXISTEN_FLAG = 2, MALLOC_ERROR = 3 };

// new
void grep(const int *const flags, char *filename, char *patterns[],
          const int file_count);
int parse_args(int *flags, char **argv, char *filenames[], char *patterns[]);
bool parse_flags(int *flags, const char *str);
int get_patterns_from_file(char *filename, char *patterns[], int *idx);

// mini-helper
int get_file_count(char *filenames[]);
int get_patterns_count(char *patterns[]);
void reset_e_f(int *flags);
void free_malloc_array(char *array[]);

// err messages
void print_err(int err_code);
void print_malloc_err();
void print_usage_err();
void print_no_file_err(const char *filename);
// old
/* bool match_pattern(const struct flags f, const char *str, char *patterns[],
 */
/*                    char *matches[]); */
/* bool get_pattern(const char *argv, const struct flags f, char *ret); */
/* int get_flags(struct flags *f, int *opt, int argc, char **argv); */
/* void handle_header(const struct flags f, const char *filename, */
/*                    const int file_count); */
/* void handle_count(const struct flags f, const int matched_lines); */
/* void handle_list_files(const struct flags f, const char *filename, */
/*                        const int matched_lines); */
/* void handle_number(const struct flags f, const int line_num); */
/* void handle_header_cl(const struct flags f, const char *filename, */
/*                       const int file_count); */

#endif  // SRC_GREP_S21_GREP_H_
