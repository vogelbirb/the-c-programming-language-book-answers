#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

enum token_type {
    SYMBOL = 1,
    COMMENT = 2,
    LITERAL = 3,
    WORD = 4,
    NEWLINE = 5,
};

char *alloc(const size_t len);
size_t _getline(char *s, const int lim);
int atoi(const char *s);
void swap(void *v[], int i, int j);
void _qsort(char *v[], int left, int right);
int detab(char line[], int length, int tab_size);
int numcmp(const char *s1, const char *s2);
void _strrev(char *s);
void linerev(char *s[], size_t len);
void insert(char *s, const char c);
int getch(void);
void ungetch(int c);
void disp_array(const char *array, size_t length);
int get_token(char *token, const size_t len);

#endif