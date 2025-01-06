#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

/* buffer for ungetch */
/* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
/* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


/* getfloat: get next integer from input into *pn */
int getfloat(double *pn)
{
    int c;
    *pn = 0;
    
    while (isspace(c = getch())) /* skip white space */
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }

    int sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    
    for (*pn = 0.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
    }

    if (c == '.') {
        c = getch();
    }

    double power = 1.0;
    for (;isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10;
    }

    *pn = sign * *pn / power;

    if (c != EOF) {
        ungetch(c);
    }

    return (int)c; 
}

int main(void) {
    double arr[5] = {0};
    for (size_t i = 0; getfloat(&arr[i]) != EOF && i < 5 ; i++) {
        printf("got: %f\n", arr[i]);
    }
    return 0;
}
