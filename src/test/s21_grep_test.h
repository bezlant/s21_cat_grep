#ifndef SRC_TEST_S21_GREP_TEST_H_
#define SRC_TEST_S21_GREP_TEST_H_
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\e[0m"

#define RED "\e[0;91m"
#define GREEN "\e[0;92m"
#define BLUE "\e[0;94m"

void run_tests(void);
void run_testcase(Suite *testcase);

Suite *suite_combinations(void);

void pretty_print(char *grep, char *s21_grep, int val, int _i);
void get_flags(char *flags, int _i, char *e_pattern, char *search_pattern,
               char *f_file);
#endif  // SRC_TEST_S21_GREP_TEST_H_
