#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

int main(const int argc, const char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: diff file1 file2\n");
        return 1;
    }
    FILE *file1;
    FILE *file2;

    if ((file1 = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error: cannot open file 1.\n");
        return 1;
    }
    if ((file2 = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "Error: cannot open file 2.\n");
        return 1;
    }

    char   line1[MAXLINE];
    char   line2[MAXLINE];
    size_t line = 1;
    while (fgets(line1, MAXLINE, file1) != NULL && fgets(line2, MAXLINE, file2) != NULL) {
        if (strcmp(line1, line2) != 0) {
            printf("%4zu\t%s", line, line1);
            printf("%4zu\t%s", line, line2);
            break;
        }
        line++;
    }
    fclose(file1);
    fclose(file2);
    return 0;
}