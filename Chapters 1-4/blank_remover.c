// AKA whitespace

#include <stdio.h>
#include <stdbool.h>

int main() {
    int c = '\0';
    bool space = false;

    while ((c = getchar()) != EOF) {
        if (c != ' ' || !space) {
            putchar(c);
        }
        space = c == ' ';
    }
    return 0;
}