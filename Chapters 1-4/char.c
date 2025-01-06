#include <stdio.h>
#include <stdbool.h>

int main() {
    // char str[] = {};
    int c; 
    long i = 0, lines = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            ++lines;
        }
        putchar(c);
        ++i;
    }
    printf("\nTotal chars: %ld, Newlines: %ld\n", i, lines);
    return 0;
}