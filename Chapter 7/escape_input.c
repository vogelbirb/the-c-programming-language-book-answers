#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

static inline int round_div(const int x, const int y) { return (x % y == 0) ? x / y : x / y + 1; }

int main(const int argc, const char *argv[]) {
    // Maximum length to be displayed without braking, not including the length of escape characters
    const int max_len = (argc > 1) ? (int)atof(argv[1]) : 10;

    char line[MAXLINE] = {0};
    int len = 0;
    while ((len = _getline(line, MAXLINE)) != -1) {
        // Brake long text lines
        for (size_t i = 0; i < round_div(len, max_len); i++) {
            // Space to fit every single character being an escape
            char escaped_line[max_len * 3];
            char *p = &line[i * max_len];
            char *t = escaped_line;
            while (*p && (p - line) < max_len + (i * max_len)) {
                if (isprint(*p)) {
                    *t = *p;
                    t++;
                } else {
                    char hex_code[4];
                    sprintf(hex_code, "\\%.2X", *p);
                    strcat(t, hex_code);
                    t += 3;
                }
                p++;
            }
            *t = '\0';
            printf("%s\n", escaped_line);
        }
    }
    return 0;
}