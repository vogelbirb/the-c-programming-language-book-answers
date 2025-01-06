#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "common.h"

size_t _getline(char *s, const int lim) {
    char *s_start = s;
    
    size_t count = 0;
    bool eof = false;
    while ((*s = getchar()) != EOF && *s != '\n' && count < lim) {
        count++;
        s++;
    }
    eof = *s == EOF;

    if (*s == '\n') {
        *s++ = '\n';
        count++;
    } 
    *s = '\0';

    if (eof) {
        return -1;
    } else {
        return count;
    }
}

#define BUFF_LEN 10000
static char buff[BUFF_LEN] = {0};
static char *buff_ptr = buff;

char *alloc(const size_t len) {
    if(BUFF_LEN - (buff_ptr - buff) >= len) {
        buff_ptr += len;
        return buff_ptr - len;  
    } else {
        return NULL;
    }
}

// Basic conversion from string to integer.
int atoi(const char *s) {
    int n = 0;
    while (*s && *s >= '0' && *s <= '9') {
        n = 10 * n + (*s++ - '0');
    }
    return n;
}

void swap(void *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* qsort: sort v[left]...v[right] into increasing order */
void _qsort(char *v[], int left, int right)
{
    int i, last;
    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
    swap((void *)v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap((void *)v, ++last, i);
    swap((void *)v, left, last);
    _qsort((void *)v, left, last-1);
    _qsort((void *)v, last+1, right);
}

// Including spaces added by tabs
#define MAXLINE 100
#define TAB_LENGTH 8

int detab(char line[], int length, int tab_size) {
    int c, i = 0;
    
    while (i < length && (c = getchar()) != EOF && c != '\n') {
        if (c == '\t') {
            while (i % tab_size != 0) {
                line[i] = ' ';
                ++i;
            }
        } else {
            line[i] = c;
            ++i;
        }
    }
    
    line[i] = '\0';

    if (c == EOF) {
        return -1;
    } 
    return i;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}


void _strrev(char *s) {
    char *p1 = s;
    char *p2 = s + strlen(s) - 1;

    while (p2 > p1) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;

        p1++;
        p2--;
    }
}

void linerev(char *s[], const size_t len) {
    char **p1 = &s[0];
    char **p2 = &s[len - 1];
    size_t len_p1;
    size_t len_p2;
    
    while (p2 > p1) {
        char *temp = *p1;
        *p1 = *p2;
        *p2 = temp; 

        p1++;
        p2--;
    }
}

void insert(char *s, const char c) {
    char *t = s + strlen(s);
    while (t >= s) {
        *t = *t;
        --t;
    }
    *t = c; 
}

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

void disp_array(const char *array, size_t length) {
    printf("\""); // Start with a quote for a string-like display

    for (size_t i = 0; i < length; ++i) {
        char c = array[i];
        switch (c) {
            case '\n': printf("\\n"); break; // Newline
            case '\t': printf("\\t"); break; // Tab
            case '\r': printf("\\r"); break; // Carriage return
            case '\\': printf("\\\\"); break; // Backslash
            case '\"': printf("\\\""); break; // Double quote
            default:
                if (isprint((unsigned char)c)) {
                    // Print printable characters directly
                    putchar(c);
                } else {
                    // Use hexadecimal escape for non-printable characters, except NULL
                    if (c != '\0') {
                        printf("\\x%02x", (unsigned char)c);
                    } else {
                        printf("\\0");
                    }
                }
                break;
        }
    }

    printf("\""); // End with a quote
    printf("\n");
}