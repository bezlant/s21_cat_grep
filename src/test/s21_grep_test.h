#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define BBLK "\e[1;30m"
#define RESET "\e[0m"

//#define HBLK "\e[0;90m"
#define RED "\e[0;91m"
#define GREEN "\e[0;92m"
//#define HYEL "\e[0;93m"
#define BLUE "\e[0;94m"
//#define HMAG "\e[0;95m"
//#define HCYN "\e[0;96m"
//#define HWHT "\e[0;97m"

void run_tests(void);
void run_testcase(Suite *testcase);

Suite *suite_combinations(void);

void pretty_print(char *grep, char *s21_grep, int val, int _i);
void get_flags(char *flags, int _i, char *e_pattern, char *search_pattern,
               char *f_file);
