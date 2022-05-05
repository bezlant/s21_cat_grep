#include "grep.h"

int main(int argc, char **argv) {
    int opt;
    flags f = {0};
    int err = get_flags(&f, &opt, argc, argv);
    if (!err) {
        for (int i = optind; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (!file) {
                if (!f.s && ((!f.e && !f.f) || i != 2))
                    printf("grep: %s: No such file or directory\n", argv[i]);
            } else {
                grep(f, file, argv[i], i);
                fclose(file);
            }
        }
    }
    return err;
}

void grep(flags f, FILE *file, char *filename, int idx) {
    static char reg_buff[BUFF_SIZE] = {'\0'};
    if (f.e && idx == 2) {
        strcpy(reg_buff, filename);
        handle_regexp();
    }
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
        default:
            printf("usage: grep [-ivclnhso] [-e pattern] [-f file] [pattern] "
                   "[file]\n");
            ret = 1;
        }
    }
    return ret;
}
