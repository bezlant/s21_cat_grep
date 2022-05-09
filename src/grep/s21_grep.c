#include "s21_grep.h"

int main(int argc, char **argv) {
    char *filenames[BUFF_SIZE] = {NULL};
    char *patterns[BUFF_SIZE] = {NULL};
    int flag['z'] = {0};

    // 0 success, 1 if no file, 2 if non existen flag 3 malloc error
    int err_code = argc >= 3 ? parse_args(flag, argv, filenames, patterns)
                             : NON_EXISTEN_FLAG;

    if (err_code == SUCCESS) {
        int file_count = get_file_count(filenames);
        for (int i = 0; filenames[i]; i++)
            grep(flag, filenames[i], patterns, file_count);
    }
    for (int i = 0; patterns[i]; i++)
        printf("patterns[%d]:%s\n", i, patterns[i]);

    for (int i = 0; filenames[i]; i++)
        printf("filenames[%d]:%s\n", i, filenames[i]);

    print_err(err_code);
    free_malloc_array(filenames);
    free_malloc_array(patterns);
    return err_code;
}

int parse_args(int *flags, char **argv, char *filenames[], char *patterns[]) {
    int err = SUCCESS;
    int p = 0;
    int f = 0;
    for (int i = 1; argv[i]; i++) {
        // returns 1 if flags set
        if (parse_flags(flags, argv[i])) {
            // ![attention] move idx to next arg for parsing
            i++;
            if ((flags['e'] || flags['f']) && !argv[i]) {
                err = NO_FILE;
                break;
            }
            // get pattern
            if (flags['e']) {
                patterns[p] = malloc(sizeof(char) * (strlen(argv[i]) + 1));
                if (!patterns[p]) {
                    err = MALLOC_ERROR;
                    break;
                }
                strcpy(patterns[p], argv[i]);
                p++;
                // got pattern move idx to next arg for parsing
            } else if (flags['f']) {
                // read patterns from file & get error
                if ((err = get_patterns_from_file(argv[i], patterns, &p)) !=
                    SUCCESS) {
                    break;
                }
            }
            reset_e_f(flags);
        } else {
            // get file to grep
            filenames[f] = malloc(sizeof(char) * (strlen(argv[i]) + 1));
            if (!filenames[f]) {
                err = MALLOC_ERROR;
                break;
            }
            strcpy(filenames[f], argv[i]);
            f++;
        }
    }
    patterns[p] = NULL;
    filenames[f] = NULL;
    return err;
}

int get_patterns_from_file(char *filename, char *patterns[], int *idx) {
    int err = SUCCESS;
    FILE *file = fopen(filename, "r");
    if (!file) {
        err = NO_FILE;
    } else {
        char *pat = malloc(1);
        size_t linecap = 0;
        ssize_t linelen = 0;
        while ((linelen = getline(&pat, &linecap, file)) > 0) {
            patterns[*idx] = malloc(sizeof(char) * linelen);
            if (!patterns[*idx]) {
                err = MALLOC_ERROR;
            }
            strcpy(patterns[*idx], pat);
            patterns[*idx][strcspn(patterns[*idx], "\r\n")] = '\0';
            (*idx)++;
        }
        free(pat);
    }
    return err;
}

bool parse_flags(int *flags, const char *str) {
    bool is_set = false;
    if (str[0] == '-') {
        for (int i = 1; str[i]; i++)
            flags[(int)str[i]] = 1;
        is_set = true;
    }
    return is_set;
}
void grep(const int *const flags, char *filename, char *patterns[],
          const int file_count) {
    return;
}

/* void grep(const struct flags f, char *filename, char *patterns[], */
/*           const int file_count) { */
/*     FILE *file = fopen(filename, "r"); */
/*     if (file) { */
/*         char *line = NULL; */
/*         size_t linecap = 0; */
/*         int matched_lines = 0; */
/*         int line_num = 0; */

/*         while (getline(&line, &linecap, file) > 0) { */
/*             line_num++; */
/*             char *matches[BUFF_SIZE]; */
/*             // everything without -o */
/*             if (match_pattern(f, line, patterns, matches)) { */
/*                 matched_lines++; */
/*                 if (!f.c && !f.l) { */
/*                     handle_header(f, filename, file_count); */
/*                     handle_number(f, line_num); */
/*                     if (f.o) { */
/*                         for (int i = 0; matches[i]; i++) { */
/*                             printf("%s\n", matches[i]); */
/*                             free(matches[i]); */
/*                         } */

/*                     } else { */
/*                         printf("%s", line); */
/*                     } */
/*                 } */
/*             } */
/*         } */
/*         handle_header_cl(f, filename, file_count); */
/*         handle_count(f, matched_lines); */
/*         handle_list_files(f, filename, matched_lines); */
/*         fclose(file); */
/*     } else if (!f.s) { */
/*         print_no_file(filename); */
/*     } */
/* } */

/* bool match_pattern(const struct flags f, const char *str, char *patterns[],
 */
/*                    char *matches[]) { */
/*     regex_t regex; */
/*     // fix to work with array of patterns */
/*     if (f.i) */
/*         regcomp(&regex, patterns, REG_ICASE); */
/*     else */
/*         regcomp(&regex, patterns, REG_EXTENDED); */
/*     regmatch_t match; */
/*     size_t offset = 0; */
/*     size_t str_len = strlen(str); */
/*     int idx = 0; */
/*     for (bool ret; (ret = regexec(&regex, str + offset, 1, &match, 0)) == 0;
 */
/*          idx++) { */
/*         int len = match.rm_eo - match.rm_so; */
/*         matches[idx] = malloc(len + 1); */
/*         memcpy(matches[idx], str + match.rm_so + offset, len); */
/*         matches[idx][len] = '\0'; */
/*         offset += match.rm_eo + 1; */
/*         if (offset > str_len) */
/*             break; */
/*     } */
/*     matches[idx] = NULL; */

/*     regfree(&regex); */
/*     return f.v ? !idx : idx; */
/* } */
/* void handle_header_cl(const struct flags f, const char *filename, */
/*                       const int file_count) { */
/*     if (f.c && !f.h && file_count > 1) */
/*         printf("%s:", filename); */
/* } */
/* void handle_number(const struct flags f, const int line_num) { */
/*     if (f.n) */
/*         printf("%d:", line_num); */
/* } */
/* void handle_list_files(const struct flags f, const char *filename, */
/*                        const int matched_lines) { */
/*     if (f.l && matched_lines) */
/*         printf("%s\n", filename); */
/* } */
/* void handle_count(const struct flags f, const int matched_lines) { */
/*     if (f.c) { */
/*         printf("%d\n", f.l ? matched_lines > 0 : matched_lines); */
/*     } */
/* } */
/* void handle_header(const struct flags f, const char *filename, */
/*                    const int file_count) { */
/*     if (!f.h && file_count > 1) */
/*         printf("%s:", filename); */
/* } */

/* bool get_pattern(const char *argv, const struct flags f, char *ret) { */
/*     int err = 0; */
/*     if (f.f) { */
/*         FILE *file = fopen(argv, "r"); */
/*         if (!file) { */
/*             err = 1; */
/*         } else { */
/*             char *pat = malloc(1); */
/*             size_t linecap = 0; */
/*             getline(&pat, &linecap, file); */
/*             strcpy(ret, pat); */
/*             ret[strcspn(ret, "\r\n")] = 0; */
/*             fclose(file); */
/*             free(pat); */
/*         } */
/*     } else { */
/*         strcpy(ret, argv); */
/*     } */

/*     optind++;  // ![warning](global variable) */
/*     return err; */
/* } */

/* int get_flags(struct flags *f, int *opt, const int argc, char **argv) { */
/*     int ret = 0; */
/*     while ((*opt = getopt(argc, argv, "eivclnhsfo?")) != -1) { */
/*         switch (*opt) { */
/*         case 'e': */
/*             f->e = true; */
/*             break; */
/*         case 'i': */
/*             f->i = true; */
/*             break; */
/*         case 'v': */
/*             f->v = true; */
/*             break; */
/*         case 'c': */
/*             f->c = true; */
/*             break; */
/*         case 'l': */
/*             f->l = true; */
/*             break; */
/*         case 'n': */
/*             f->n = true; */
/*             break; */
/*         case 'h': */
/*             f->h = true; */
/*             break; */
/*         case 's': */
/*             f->s = true; */
/*             break; */
/*         case 'f': */
/*             // ![attention] NOT SURE if NEEDED */
/*             f->f = true; */
/*             break; */
/*         case 'o': */
/*             f->o = true; */
/*             break; */
/*         case '?': */
/*             ret = 1; */
/*         } */
/*     } */
/*     return ret; */
/* } */
void print_usage_err() {
    printf("usage: grep [-ivclnhso] [-e pattern] [-f file] template "
           "[file ...]\n");
}

void print_no_file_err(const char *filename) {
    printf("grep: %s: No such file or directory\n", filename);
}

void free_malloc_array(char *array[]) {
    for (int i = 0; array[i]; i++)
        free(array[i]);
}

void reset_e_f(int *flags) {
    flags['e'] = 0;
    flags['f'] = 0;
}

int get_patterns_count(char *patterns[]) {
    int count = 0;
    while (*patterns++)
        count++;
    return count;
}

int get_file_count(char *filenames[]) {
    int count = 0;
    while (*filenames++)
        count++;
    return count;
}
void print_err(int err_code) {
    if (err_code == NON_EXISTEN_FLAG)
        print_usage_err();
    if (err_code == MALLOC_ERROR)
        print_malloc_err();
}
void print_malloc_err() {
    printf("grep: [MALLOC]: Can't allocate enough memory!:(\n");
}
