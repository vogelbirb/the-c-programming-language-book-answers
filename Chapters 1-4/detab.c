#include <stdio.h>
#include <stdbool.h>
// Including spaces added by tabs
#define MAXLINE 100
#define TAB_LENGTH 8

int detab(char line[], int length, int tab_size);

int main() {
    char line[MAXLINE] = "";
    while (detab(line, MAXLINE, TAB_LENGTH) != -1) {
        printf("%s\n", line);
    }
    return 0;
}

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
