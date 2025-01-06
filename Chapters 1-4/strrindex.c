#include <stdio.h>

#define MAXLINE 1000

int _getline(char s[], int limit);
int strrindex(char s[], char t[]);

char pattern[] = "hello"; // Pattern to search for

int main() {
    char line[MAXLINE] = "";
    int found = 0;
    int rightmost_pos = 0;

    while (_getline(line, MAXLINE) > 0) {
        if ((rightmost_pos = strrindex(line, pattern)) >= 0) {
            printf("[%i %c] %s\n", rightmost_pos, line[rightmost_pos], line);
            found++;
        }
    }
    return found;
}

int _getline(char s[], int limit) {
    int c = '\0', i = 0;
    
    for (;(c = getchar()) != EOF && c != '\n'; i++) {
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

/* strindex: return index of t in s, -1 if none */
int strrindex(char s[], char t[]) {
    int max = -1;
    int i = 0;
    for (i = 0; s[i] != '\0'; i++) {
        int j, k;
        for (j = i, k = 0; t[k] != '\0' && s[j]==t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0') {
            max = i;
        }
    }
    return max;
}