#include <stdio.h>
#include <stdbool.h>
#define MAXLINE 100

int remove_comments(char line[], int length);

int main() {
    char line[MAXLINE] = "";

    while (remove_comments(line, MAXLINE) != -1) {
        if (line[0] != '\0') {
            printf("%s", line);
        }
    }
    return 0;
}

// Returns index 0 as \0 for removed lines
// Returns -1 for EOF
// Does not handle multi-line comments
int remove_comments(char line[], int length) {
    int c, i = 0;
    bool comment = false;
    bool appending = false; 

    while (i < length - 1 && (c = getchar()) != EOF && c != '\n') {
        if (c != ' ' && c != '\t' && c != '/') {
            appending = true;
        }
      if (i > 0 && c == '/' && line[i - 1] == '/' && !comment) {
            comment = true;
            if (!appending) {
                line[0] = '\0';
            } else {
                line[i - 1] = '\n';
                line[i] = '\0';
            }
            ++i;
        } 
        line[i] = c;
        ++i;
    }
    
    if (i == 0 && c == EOF) {
        return -1;
    }
    
    if (!comment) {
        line[i] = '\n';
        line[i + 1] = '\0';
    }
    return 0;
}