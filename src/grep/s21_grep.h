#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 4096

enum { SUCCESS = 0, NO_FILE = 1, NON_EXISTENT_FLAG = 2, MALLOC_ERROR = 3 };

// new
void grep(const int *const flags, char *filename, char *patterns[],
          const int file_count);
int parse_args(int *flags, char **argv, char *filenames[], char *patterns[],
               int argc);
bool parse_flags(int *flags, const char *str);
bool check_flags(char *argv);
int get_patterns_from_file(char *filename, char *patterns[], int *idx);
bool match_patterns(const int *const flags, const char *str, char *patterns[],
                    char *matches[]);
void handle_header(const int *const flags, const char *filename,
                   const int file_count);
void handle_number(const int *const flags, const int line_num);
void handle_header_cl(const int *const flags, const char *filename,
                      const int file_count);
void handle_count(const int *const flags, const int matched_lines);
void handle_list_files(const int *const flags, const char *filename,
                       const int matched_lines);
// mini-helper
int get_file_count(char *filenames[]);
void reset_e_f(int *flags);
void free_malloc_array(char *array[]);

// err messages
void print_err(int err_code);
void print_malloc_err();
void print_usage_err();
void print_no_file_err(char *filename);

#endif  // SRC_GREP_S21_GREP_H_
