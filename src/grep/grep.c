#include "grep.h"

int main(int argc, char **argv) {
    int opt;
    opterr = 0;  // prevent getopt from printing it's own error
    flags f = {0};
    int err = get_flags(&f, &opt, argc, argv);
    if (argv[optind] == NULL || argv[optind + 1] == NULL)
        err = 1;
    if (!err) {
        char pattern[BUFF_SIZE] = {'\0'};
        if (get_pattern(argv[optind], f, pattern))
            print_no_file(argv[optind]);
        else
            for (int i = optind; i < argc; i++)
                grep(f, argv[i], pattern);
    } else
        print_usage();

    return err;
}

void grep(flags f, char *filename, char *pattern) {
    FILE *file = fopen(filename, "r");
    if (file) {
        char *line = NULL;
        size_t linecap = 0;
        while (getline(&line, &linecap, file) > 0) {
            printf("%s\n", line);
            if (match_pattern(f, line, pattern))
                printf("%s\n", line);
        }
    } else {
        printf("grep: %s: No such file or directory\n", filename);
    }

    fclose(file);
}

bool match_pattern(flags f, char *str, char *pattern) {
    bool ret = false;
    regex_t regex;
    if (f.i)
        regcomp(&regex, pattern, REG_ICASE);
    else
        regcomp(&regex, pattern, REG_EXTENDED);
    ret = regexec(&regex, pattern, 0, NULL, 0);

    regfree(&regex);
    return f.v ? !ret : ret;
}

bool get_pattern(char *argv, flags f, char *ret) {
    int err = 0;
    if (f.f) {
        printf("argv = %s\n", argv);

        FILE *file = fopen(argv, "r");
        if (!file) {
            err = 1;
        } else {
            char *pat = malloc(1);
            size_t linecap = 0;
            getline(&pat, &linecap, file);
            strcpy(ret, pat);
            fclose(file);
            free(pat);
        }
    } else {
        strcpy(ret, argv);
    }

    optind++;  // ![warning](global variable)
    return err;
}

int get_flags(flags *f, int *opt, int argc, char **argv) {
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

void print_no_file(char *filename) {
    printf("grep: %s: No such file or directory\n", filename);
}
