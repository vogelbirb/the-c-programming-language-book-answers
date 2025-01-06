#include "common.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

int getword(char *word, int lim);

int main(void) {
    char word[100];
    while (getword(word, 100) > 0) {
        printf("%s\n", word);
    }

    return 0;
}

/* getword: get next word or character from input */
// handles "string literals" as whole words
int getword(char *word, int lim) {
    int c = getch();
    char *w = word;

    while (isspace(c)) {
        c = getch();
    }

    if (c != EOF) {
        *w = c;
    }

    if (!isalpha(c) && c != '_' && c != '"') {
        *++w = '\0';
        return c;
    }

    bool inside_str = false;
    bool full_line_comment = false;
    for (size_t i = 0; i < lim && *w != EOF; i++) {
        if (*w == '"' && ((i > 0) ? *(w - 1) != '\\' : true)) {
            inside_str = inside_str ? false : true;
        }
        if (*w == '/' && ((i > 0) ? *(w - 1) == '/' : false)) {
            full_line_comment = true;
        }
        if (!inside_str && !isalnum(*w) && *w != '_' && *w != '"') {
            ungetch(*w);
            break;
        }

        *++w = getch();
    }
    *w = '\0';
    return word[0];
}