#include <stdio.h>

int main() {
    int c, lim = 15;

    // Bad
    for (int i = 0; (i < lim - 1) == (((c = getchar()) != '\n') == (c ))); ++i) {
        printf("%c", c);
    }
    printf("\n");
}