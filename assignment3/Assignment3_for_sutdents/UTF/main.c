#include <stdio.h>
#include "utf8.c"

#define ARRAY_MAX 300
#define STRING_MAX 100

struct Block {
    unsigned int start;
    unsigned int end;
    char name[STRING_MAX];
};

int size;
struct Block arr[ARRAY_MAX];
int count[ARRAY_MAX];

unsigned int convert(char *str) {
    unsigned int code = 0;
    int seed = 1;
    int len = strlen(str);
    for (int i = 0; i < strlen(str); ++i) {
        int pos = len - 1 - i;
        if (str[pos] >= 48 && str[pos] <= 57) {
            code += (str[pos] - '0') * seed;
        } else if (str[pos] >= 65 && str[pos] <= 70) {
            code += (str[pos] - 'A' + 10) * seed;
        } else {
            printf("Wrong Unicode code!");
            break;
        }
        seed *= 16;
    }
    return code;
}

int read() {
    FILE *file;
    char line[STRING_MAX * 2];
    if ((file = fopen("Blocks.txt", "r")) == NULL) {
        printf("Loading Error!");
        exit(0);
    }

    int i = 0;
    char code[STRING_MAX];
    while (!feof(file)) {
        fgets(line, STRING_MAX * 2, file);
        if ((line[0] >= 48 && line[0] <= 57) || (line[0] >= 65 && line[0] <= 70)) {
            int j = 0;
            while (line[j] != ';') {
                j++;
            }
            strncpy(code, line, j);
            strncpy(arr[i].name, line + j + 2, strlen(line) - j - 3);

            int k = 0;
            while (code[k] != '.') {
                k++;
            }
            char start[k + 1];
            char end[k + 1];
            strncpy(start, code, k);
            start[k] = '\0';
            strncpy(end, code + k + 2, k);
            end[k] = '\0';

            arr[i].start = convert(start);
            arr[i].end = convert(end);

            i++;
        }
    }
    fclose(file);
    return i;
}

void search(unsigned int codepoint) {
    for (int i = 0; i < size; ++i) {
        if (codepoint >= arr[i].start && codepoint <= arr[i].end) {
            count[i]++;
            return;
        }
    }
}

void openFile() {
    FILE *file;
    if ((file = stdin) == NULL) {
        printf("No such file!");
        exit(0);
    }

    int bytes_in_char;
    unsigned char *p;
    char line[100000];

    while (!feof(file)) {
        fgets(line, sizeof(line), file);
        p = (unsigned char *) line;
        while (*p) {
            search(utf8_to_codepoint(p, &bytes_in_char));
            _utf8_incr(p);
        }

    }

    fclose(file);
}

int main(int argc, char **argv) {

    //load array
    size = read();
    
    //load file and search
    openFile();

    //find max
    int max = 0;
    for (int i = 1; i < size; ++i) {
        max = count[i] > count[max] ? i : max;
    }
    printf("%s", arr[max].name);

    return 0;
}