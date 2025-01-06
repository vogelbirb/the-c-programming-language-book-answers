#include <stdio.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
void disp_array(int arr[], int len);

int main() {
    int c;
    ungetch(EOF);
    while ((c = getch()) != EOF) {
        putchar(c);
    }
    return 0;
}

int buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void disp_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%i", i > 0 ? ", " : "", arr[i]);
    }
    printf("]\n");
}