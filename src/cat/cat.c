#include "cat.h"

static const char *const symb[255] = {
    [0] = "^@",      [1] = "^A",     [2] = "^B",     [3] = "^C",
    [4] = "^D",      [5] = "^E",     [6] = "^F",     [7] = "^G",
    [8] = "^H",      [9] = " ",      [10] = "\n",    [11] = "^K",
    [12] = "^L",     [13] = "^M",    [14] = "^N",    [15] = "^O",
    [16] = "^P",     [17] = "^Q",    [18] = "^R",    [19] = "^S",
    [20] = "^T",     [21] = "^U",    [22] = "^V",    [23] = "^W",
    [24] = "^X",     [25] = "^Y",    [26] = "^Z",    [27] = "^[",
    [28] = "^\\",    [29] = "^]",    [30] = "^^",    [31] = "^_",
    [32] = " ",      [33] = "!",     [34] = "\"",    [35] = "#",
    [36] = "$",      [37] = "%",     [38] = "&",     [39] = "'",
    [40] = "(",      [41] = ")",     [42] = "*",     [43] = "+",
    [44] = ",",      [45] = "-",     [46] = ".",     [47] = "/",
    [48] = "0",      [49] = "1",     [50] = "2",     [51] = "3",
    [52] = "4",      [53] = "5",     [54] = "6",     [55] = "7",
    [56] = "8",      [57] = "9",     [58] = ":",     [59] = ";",
    [60] = "<",      [61] = "=",     [62] = ">",     [63] = "?",
    [64] = "@",      [65] = "A",     [66] = "B",     [67] = "C",
    [68] = "D",      [69] = "E",     [70] = "F",     [71] = "G",
    [72] = "H",      [73] = "I",     [74] = "J",     [75] = "K",
    [76] = "L",      [77] = "M",     [78] = "N",     [79] = "O",
    [80] = "P",      [81] = "Q",     [82] = "R",     [83] = "S",
    [84] = "T",      [85] = "U",     [86] = "V",     [87] = "W",
    [88] = "X",      [89] = "Y",     [90] = "Z",     [91] = "[",
    [92] = "\\",     [93] = "]",     [94] = "^",     [95] = "_",
    [96] = "`",      [97] = "a",     [98] = "b",     [99] = "c",
    [100] = "d",     [101] = "e",    [102] = "f",    [103] = "g",
    [104] = "h",     [105] = "i",    [106] = "j",    [107] = "k",
    [108] = "l",     [109] = "m",    [110] = "n",    [111] = "o",
    [112] = "p",     [113] = "q",    [114] = "r",    [115] = "s",
    [116] = "t",     [117] = "u",    [118] = "v",    [119] = "w",
    [120] = "x",     [121] = "y",    [122] = "z",    [123] = "{",
    [124] = "|",     [125] = "}",    [126] = "~",    [127] = "^?",
    [128] = "M-^@",  [129] = "M-^A", [130] = "M-^B", [131] = "M-^C",
    [132] = "M-^D",  [133] = "M-^E", [134] = "M-^F", [135] = "M-^G",
    [136] = "M-^H",  [137] = "M-^I", [138] = "M-^J", [139] = "M-^K",
    [140] = "M-^L",  [141] = "M-^M", [142] = "M-^N", [143] = "M-^O",
    [144] = "M-^P",  [145] = "M-^Q", [146] = "M-^R", [147] = "M-^S",
    [148] = "M-^T",  [149] = "M-^U", [150] = "M-^V", [151] = "M-^W",
    [152] = "M-^X",  [153] = "M-^Y", [154] = "M-^Z", [155] = "M-^[",
    [156] = "M-^\\", [157] = "M-^]", [158] = "M-^^", [159] = "M-^_",
};

static const char pos_fl[][SIZE] = {
    "-b", "--number-nonblank", "-e", "-E", "-n",  "--number",
    "-s", "--squeeze-blank",   "-t", "-T", "NULL"};

int main(int argc, char **argv) {
    int ret = 0;
    if (check_args(argc, argv)) {
        flags f = {0};
        f.is_set = parse_flag(&f, argv[1]);
        for (int i = 1 + f.is_set; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            int cnt = 1;
            if (!file) {
                printf("cat: %s: No such file or directory\n", argv[i]);
                continue;
            } else {
                print_file(f, file, &cnt);
                fclose(file);
            }
        }
    } else {
        printf("usage: cat [-benst] [file ...]\n");
        ret = 1;
    }

    return ret;
}

bool check_args(const int count, char **strs) {
    bool ret = false;
    if (count == 2 && strs[1][0] != '-')
        ret = true;
    if (count > 2 && check_flags(strs[1]))
        ret = true;

    return ret;
}

bool check_flags(const char *flags) {
    bool ret = flags[0] == '-' ? false : true;
    if (flags[0] == '-') {
        for (int i = 0; strcmp("NULL", pos_fl[i]); i++) {
            if (!strcmp(pos_fl[i], flags)) {
                ret = true;
                break;
            }
        }
    }
    return ret;
}

bool parse_flag(flags *f, const char *str) {
    bool ret = *str == '-' ? true : false;
    if (!strcmp(str, pos_fl[b]) || !strcmp(str, pos_fl[gnu_b]))
        f->b = true;
    if (!strcmp(str, pos_fl[e]))
        f->e = true;
    if (!strcmp(str, pos_fl[gnu_e]))
        f->E = true;
    if (!strcmp(str, pos_fl[n]) || !strcmp(str, pos_fl[gnu_n]))
        f->n = true;
    if (!strcmp(str, pos_fl[s]))
        f->s = true;
    if (!strcmp(str, pos_fl[t]))
        f->t = true;
    if (!strcmp(str, pos_fl[gnu_t]))
        f->T = true;
    return ret;
}

void print_file(flags f, FILE *file, int *cnt) {
    char *line = NULL;
    size_t lencap = 0;
    ssize_t linelen;

    while ((linelen = getline(&line, &lencap, file)) > 0) {
        if (f.is_set)
            handle_string(f, line, linelen, cnt);
        else
            fwrite(line, linelen, 1, stdout);
    }
    // must free getline doest malloc
    free(line);
}

void handle_string(flags f, char *str, size_t len, int *cnt) {
    if (f.b)
        handle_b(f, str, len, cnt);
    else if (f.s)
        handle_s(f, str, len);
    else if (f.n)
        handle_n(f, str, len, cnt);
    else if (f.e)
        handle_e(f, str, len);
    else if (f.E)
        handle_E(f, str, len);
    else if (f.T)
        handle_T(f, str, len);
    else if (f.t)
        handle_t(f, str, len);
    else
        fwrite(str, len, 1, stdout);
}
void handle_t(flags f, const char *str, size_t len) {
    for (int i = 0; i < len; i++) {
        if (str[i] == '\t')
            printf("^I");
        else
            printf("%s", symb[(int)str[i]]);
    }
}

void handle_e(flags f, const char *str, size_t len) {
    for (int i = 0; i < len; i++) {
        if (str[i] == '\n')
            printf("$\n");
        else if (str[i] == '\t')
            printf("\t");
        else
            printf("%s", symb[(int)str[i]]);
    }
}

void handle_T(flags f, const char *str, size_t len) {
    for (int i = 0; i < len; i++) {
        if (str[i] == '\t')
            printf("^I");
        else
            printf("%c", str[i]);
    }
}

void handle_E(flags f, char *str, size_t len) {
    if (str[len - 1] == '\n') {
        char *tmp = malloc(len + 1);
        strcpy(tmp, str);
        tmp[len - 1] = '$';
        tmp[len] = '\n';
        fwrite(tmp, len + 1, 1, stdout);
        free(tmp);
    } else {
        fwrite(str, len, 1, stdout);
    }
}

void num_to_str(int val, char *num) {
    int idx;
    for (idx = SIZE - 2; val; val /= 10, idx--)
        num[idx] = val % 10 + '0';
    memmove(num, num + idx + 1, SIZE - idx);
}

void handle_b(flags f, char *str, size_t len, int *cnt) {
    char num[SIZE] = {'\0'};
    num_to_str(*cnt, num);
    if (*str != '\n') {
        printf("     %s\t", num);
        fwrite(str, len, 1, stdout);
        (*cnt)++;
    } else {
        fwrite(str, len, 1, stdout);
    }
}
void handle_s(flags f, char *str, size_t len) {
    static int prev = 0;
    if (*str != '\n' || !prev) {
        fwrite(str, len, 1, stdout);
        prev = 0;
    } else {
        prev = 1;
    }
}
void handle_n(flags f, char *str, size_t len, int *cnt) {
    char num[SIZE] = {'\0'};
    num_to_str(*cnt, num);
    printf("     %s\t", num);
    fwrite(str, len, 1, stdout);
    (*cnt)++;
}
