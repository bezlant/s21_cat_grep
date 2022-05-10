#include "s21_grep_test.h"
static const char *const s21_grep_flags[10] = {
    [0] = " -e ", [1] = " -i ", [2] = " -v ", [3] = " -c ", [4] = " -l ",
    [5] = " -n ", [6] = " -h ", [7] = " -s ", [8] = " -f ", [9] = " -o "};

START_TEST(test_combinations_1) {
    char f_file[] = " void ";
    char e_pattern[] = " void -e Lorem";
    char search_files[] = " v2 void char text";
    char search_pattern[] = " void Lorem";
    char grep[512] = "grep --color=never ";
    char s21_grep[512] = "./s21_grep ";
    char flags[512] = "";

    get_flags(flags, _i, e_pattern, search_pattern, f_file);

    strcat(grep, flags);
    strcat(grep, search_files);
    strcat(grep, " > tmp1");

    strcat(s21_grep, flags);
    strcat(s21_grep, search_files);
    strcat(s21_grep, " > tmp2");

    system("echo > tmp1");
    system("echo > tmp2");
    if (!system(grep)) {
        system(s21_grep);
        int val = system("diff tmp1 tmp2");
        pretty_print(grep, s21_grep, val, _i);
        char str[2048];
        sprintf(str, "\nTEST N:%d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep,
                RESET);
        ck_assert_msg(val == 0, str);
    }
}
END_TEST

START_TEST(test_combinations_2) {
    char f_file[] = " char ";
    char e_pattern[] = " void -e Lorem";  //-e Lorem ";
    char search_files[] = " v2 void char text";
    char search_pattern[] = " void Lorem";
    char grep[512] = "grep --color=never ";
    char s21_grep[512] = "./s21_grep ";
    char flags[512] = "";

    get_flags(flags, _i, e_pattern, search_pattern, f_file);

    strcat(grep, flags);
    strcat(grep, search_files);
    strcat(grep, " > tmp1");

    strcat(s21_grep, flags);
    strcat(s21_grep, search_files);
    strcat(s21_grep, " > tmp2");

    if (!system(grep)) {
        system(s21_grep);
        int val = system("diff tmp1 tmp2");
        pretty_print(grep, s21_grep, val, _i);
        char str[2048];
        sprintf(str, "\nTEST N:%d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep,
                RESET);
        ck_assert_msg(val == 0, str);
    }
}
END_TEST

START_TEST(test_combinations_3) {
    char f_file[] = " char ";
    char e_pattern[] = " void";  //-e Lorem ";
    char search_files[] = " v2 ";
    char search_pattern[] = " void Lorem";
    char grep[512] = "grep --color=never ";
    char s21_grep[512] = "./s21_grep ";
    char flags[512] = "";

    get_flags(flags, _i, e_pattern, search_pattern, f_file);

    strcat(grep, flags);
    strcat(grep, search_files);
    strcat(grep, " > tmp1");

    strcat(s21_grep, flags);
    strcat(s21_grep, search_files);
    strcat(s21_grep, " > tmp2");

    if (!system(grep)) {
        system(s21_grep);
        int val = system("diff tmp1 tmp2");
        pretty_print(grep, s21_grep, val, _i);
        char str[2048];
        sprintf(str, "\nTEST N:%d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep,
                RESET);
        ck_assert_msg(val == 0, str);
    }
}
END_TEST

START_TEST(test_combinations_4) {
    char f_file[] = " char ";
    char e_pattern[] = " char ";  //-e Lorem ";
    char search_files[] = " v2 void ";
    char search_pattern[] = " void Lorem";
    char grep[512] = "grep --color=never ";
    char s21_grep[512] = "./s21_grep ";
    char flags[512] = "";

    get_flags(flags, _i, e_pattern, search_pattern, f_file);

    strcat(grep, flags);
    strcat(grep, search_files);
    strcat(grep, " > tmp1");

    strcat(s21_grep, flags);
    strcat(s21_grep, search_files);
    strcat(s21_grep, " > tmp2");

    if (!system(grep)) {
        system(s21_grep);
        int val = system("diff tmp1 tmp2");
        pretty_print(grep, s21_grep, val, _i);
        char str[2048];
        sprintf(str, "\nTEST N:%d\n%s%s\n%s%s\n", _i, BLUE, grep, s21_grep,
                RESET);
        ck_assert_msg(val == 0, str);
    }
}
END_TEST

void get_flags(char *flags, int _i, char *e_pattern, char *search_pattern,
               char *f_file) {
    if (_i >> 0 & 1) {  // && !(_i >> 8 & 1)) {
        strcat(flags, s21_grep_flags[0]);
        strcat(flags, e_pattern);
    }
    if (_i >> 1 & 1)
        strcat(flags, s21_grep_flags[1]);
    if (_i >> 2 & 1)
        strcat(flags, s21_grep_flags[2]);
    if (_i >> 3 & 1)
        strcat(flags, s21_grep_flags[3]);
    if (_i >> 4 & 1)
        strcat(flags, s21_grep_flags[4]);
    if (_i >> 5 & 1)
        strcat(flags, s21_grep_flags[5]);
    if (_i >> 6 & 1)
        strcat(flags, s21_grep_flags[6]);
    if (_i >> 7 & 1 || 1)
        strcat(flags, s21_grep_flags[7]);
    if (_i >> 8 & 1) {  //&& !(_i >> 0 & 1)) {
        strcat(flags, s21_grep_flags[8]);
        strcat(flags, f_file);
    }
    if (_i >> 9 & 1)
        strcat(flags, s21_grep_flags[9]);
    if (!(_i >> 0 & 1) && !(_i >> 8 & 1))
        strcat(flags, search_pattern);
}

void pretty_print(char *grep, char *s21_grep, int val, int _i) {
    // printf("\033[%d;%dH", 3, 0);
    printf(
        "\nCURRENT TEST: %d / 1024\n%s%-150s\n%-150s%s\nSUCCESS: %s%-150s%s\n",
        _i, BLUE, grep, s21_grep, RESET, !val ? GREEN : RED,
        val == 0 ? "TRUE" : "FALSE", RESET);
    fflush(stdout);
}

Suite *suite_combinations(void) {
    Suite *s = suite_create("suite_combinations");
    TCase *tc = tcase_create("combinations_tc");

    system("clear");
    tcase_add_loop_test(tc, test_combinations_1, 0, 1024);
    tcase_add_loop_test(tc, test_combinations_2, 0, 1024);
    tcase_add_loop_test(tc, test_combinations_3, 0, 1024);
    tcase_add_loop_test(tc, test_combinations_4, 0, 1024);

    suite_add_tcase(s, tc);
    return s;
}
