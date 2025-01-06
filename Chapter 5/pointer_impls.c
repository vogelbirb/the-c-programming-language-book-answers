#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINE 100
#define NUMBER '0'
#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

size_t _getline(char *s, const int lim) {
    size_t count = 0;
    while ((*s = getchar()) != EOF && *s != '\n' && count < lim) {
        count++;
        s++;
    }
    if (*s =='\n') {
        *s++ = '\n';
        count++;
    }
    *s = '\0';
    return count;
}

int atoi(const char *s) {
    int n = 0;
    while (*s && *s >= '0' && *s <= '9') {
        n = 10 * n + (*s++ - '0');
    }
    return n;
}

void reverse(char *s) {
    int len = strlen(s);
    if (len < 2) {
        return;
    }
    char *t = s + len - 1;
    do {
        char temp;
        temp = *t;
        *t = *s;
        *s = temp;

    } while (--t > ++s);
}

char *itoa(int n, char *s) {
    char *start = s;
    
    int sign = n;
    if (sign < 0) {
        n = -n;
    }
    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) {
        *s++ = '-';
    }
    *s= '\0';
    
    reverse(start);
    
    return start;
}

/* strfind: return pointer to t in s, NULL if none */
char *strfind(char *s, char *t) {
    if (strlen(t) > strlen(s)) {
        return NULL;
    }

    char *s_start = s;
    while (*s_start) {
        char *cs = s_start;
        char *ts = t;
        while (*cs && *ts && *cs == *ts) {
            cs++;
            ts++;
        }
        if (*ts == '\0') {
            return s_start;
        }
        s_start++;
    }
    return NULL;
}

int getop(char *s) {
    int c;
    while ((*s = c = getch()) == ' ' || c == '\t')
        ;
    *(s + 1) = '\0';
    if (!isdigit(c) && c != '.') {
        return c;
    }
    if (isdigit(c)) {
        while (isdigit(*++s = c = getch()))
            ;
    }
    if (c == '.') {
        while (isdigit(*++s = c = getch()))
            ;
    }
    *s = '\0';
    if (c != EOF) {
        ungetch(c);
    }
    return NUMBER;
}

int main(void) {
    char line[MAXLINE] = "";
    _getline(line, MAXLINE);
    printf("gotline: %s", line);
    printf("as int: %i\n", atoi(line));
    char str[MAXLINE] = "";
    printf("as str: %s\n", itoa(atoi(line), str));
    printf("str[4] = %i\n", str[3]);
    char end[] = "1";
    printf("strindex: %s\n", strfind(str, end));
    char str2[MAXLINE] = "";
    getop(str2);
    printf("getop: %f\n", atof(str2));
    getop(str2);
    printf("getop: %f\n", atof(str2));
    return 0;
}