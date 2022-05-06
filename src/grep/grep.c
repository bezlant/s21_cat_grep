#include "grep.h"

int main(int argc, char **argv) {
    int opt;
    opterr = 0;  // prevent getopt from printing it's own error
    struct flags f = {0};
    int err = get_flags(&f, &opt, argc, argv);
    if (argv[optind] == NULL || argv[optind + 1] == NULL)
        err = 1;
    if (!err) {
        char pattern[BUFF_SIZE] = {'\0'};
        if (get_pattern(argv[optind], f, pattern) && !f.s)
            print_no_file(argv[optind]);
        else
            for (int i = optind; i < argc; i++)
                grep(f, argv[i], pattern, argc - optind);
    } else
        print_usage();
    return err;
}

void grep(const struct flags f, const char *filename, const char *pattern,
          const int file_count) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char *line = NULL;
        size_t linecap = 0;
        int matched_lines = 0;
        int line_num = 0;

        while (getline(&line, &linecap, file) > 0) {
            line_num++;
            char *matches[100];
            // everything without -o
            if (match_pattern(f, line, pattern, matches)) {
                matched_lines++;
                if (!f.c && !f.l) {
                    handle_header(f, filename, file_count);
                    handle_number(f, line_num);
                    if (f.o)
                        for (int i = 0; matches[i]; i++) {
                            printf("%s\n", matches[i]);
                            free(matches[i]);
                        }
                    else
                        printf("%s", line);
                }
            }
        }
        handle_header_cl(f, filename, file_count);
        handle_count(f, matched_lines);
        handle_list_files(f, filename, matched_lines);
        fclose(file);
    }

    else if (!f.s) {
        print_no_file(filename);
    }
}

bool match_pattern(const struct flags f, const char *str, const char *pattern,
                   char *matches[]) {
    regex_t regex;
    if (f.i)
        regcomp(&regex, pattern, REG_ICASE);
    else
        regcomp(&regex, pattern, REG_EXTENDED);
    regmatch_t match;
    size_t offset = 0;
    size_t str_len = strlen(str);
    int idx = 0;
    for (bool ret; (ret = regexec(&regex, str + offset, 1, &match, 0)) == 0;
         idx++) {
        int len = match.rm_eo - match.rm_so;
        matches[idx] = malloc(len + 1);
        memcpy(matches[idx], str + match.rm_so + offset, len);
        matches[idx][len] = '\0';
        offset += match.rm_eo + 1;
        if (offset > str_len)
            break;
    }
    matches[idx] = NULL;

    regfree(&regex);
    return f.v ? !idx : idx;
}
void handle_header_cl(const struct flags f, const char *filename,
                      const int file_count) {
    if (f.c && !f.h && file_count > 1)
        printf("%s:", filename);
}
void handle_number(const struct flags f, const int line_num) {
    if (f.n)
        printf("%d:", line_num);
}
void handle_list_files(const struct flags f, const char *filename,
                       const int matched_lines) {
    if (f.l && matched_lines)
        printf("%s\n", filename);
}
void handle_count(const struct flags f, const int matched_lines) {
    if (f.c) {
        printf("%d\n", f.l ? matched_lines > 0 : matched_lines);
    }
}
void handle_header(const struct flags f, const char *filename,
                   const int file_count) {
    if (!f.h && file_count > 1)
        printf("%s:", filename);
}

bool get_pattern(const char *argv, const struct flags f, char *ret) {
    int err = 0;
    if (f.f) {
        FILE *file = fopen(argv, "r");
        if (!file) {
            err = 1;
        } else {
            char *pat = malloc(1);
            size_t linecap = 0;
            getline(&pat, &linecap, file);
            strcpy(ret, pat);
            ret[strcspn(ret, "\r\n")] = 0;
            fclose(file);
            free(pat);
        }
    } else {
        strcpy(ret, argv);
    }

    optind++;  // ![warning](global variable)
    return err;
}

int get_flags(struct flags *f, int *opt, const int argc, char **argv) {
    int ret = 0;
    while ((*opt = getopt(argc, argv, "eivclnhsfo?")) != -1) {
        switch (*opt) {
        case 'e':
            f->e = true;
            break;
        case 'i':
            f->i = true;
            break;
        case 'v':
            f->v = true;
            break;
        case 'c':
            f->c = true;
            break;
        case 'l':
            f->l = true;
            break;
        case 'n':
            f->n = true;
            break;
        case 'h':
            f->h = true;
            break;
        case 's':
            f->s = true;
            break;
        case 'f':
            // ![attention] NOT SURE if NEEDED
            f->i = true;
            f->f = true;
            break;
        case 'o':
            f->o = true;
            break;
        case '?':
            ret = 1;
        }
    }
    return ret;
}
void print_usage() {
    printf("usage: grep [-ivclnhso] [-e pattern] [-f file] [pattern] "
           "[file ...]\n");
}

void print_no_file(const char *filename) {
    printf("grep: %s: No such file or directory\n", filename);
}
