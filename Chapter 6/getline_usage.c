#define _GNU_SOURCE
#include <stdio.h>

int main(const int argc, const char *argv[]) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        printf("%s", line);
    }
    return 0;
}