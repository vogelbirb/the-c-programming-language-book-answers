#include <stdio.h>
#include <stdbool.h>
#define MAXLINE 100

int getline_(char line[], int length);

int main() {
    char line[MAXLINE] = {0};
    int length = 0;

    while ((length = getline_(line, MAXLINE)) != -1) {
       if (length > 0) {
        printf("%s\n", line);
       }
    }
    return 0;
}

int getline_(char line[], int length) {
    int c, i = 0;
    bool line_started = false;
    
    while (i < length && (c = getchar()) != EOF && c != '\n') {
        if (!line_started && (c == ' ' || c == '\t')) {
            continue;
        } else {
            line_started = true;
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
