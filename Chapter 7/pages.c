#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(const int argc, const char **argv) {
    const char *program = argv[0];
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [file...]\n", program);
        return 1;
    }

    char line[MAXLINE] = {0};
    for (size_t i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            fprintf(stderr, "%s: error opening %s\n", program, argv[i]);
            continue;
        }
        printf("%s: pg. %zu\n", argv[i], i);
        size_t line_num = 1;
        while (fgets(line, MAXLINE, file)) {
            // Remove newline to ensure consistent printing for EOF lines
            char *newline = strchr(line, '\n');
            if (newline != NULL) {
                *newline = '\0';
            }
            printf("%4zu\t%s\n", line_num, line);
            line_num++;
        }
    }

    return 0;
}