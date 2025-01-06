#include <stdio.h>
#define MAXLINE 1000

int _getline(char s[], int limit);
void copy(char to[], char from[]);

int main() {
    int current = 0;
    int max = 0;
    char line[MAXLINE] = {0};
    char longest[MAXLINE] = {0};
    
    while ((current = _getline(line, MAXLINE)) > 0) {
        if (current > max) {
            max = current;
            copy(longest, line);
        }
    }
    if (max > 0) {
        printf("%s\n", longest);
    }

    return 0;
}

int _getline(char s[], int limit) {
    int c = '\0', i = 0;
    
    for (;(c = getchar()) != EOF && c != '\n'; ++i) {
        // Fix to allow long lines to be counted correctly
        if (i < limit - 1) {
            s[i] = c;
        }
    }
    if (c == '\n') {
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    for (int i = 0; (to[i] = from[i]) != '\0'; ++i) {}
}