#include <stdio.h>
#define MAXLINE 100

void reverse(char s[]);
int getline_(char line[], int length);

int main() {
    char s[MAXLINE] = "";
    getline_(s, MAXLINE);

    reverse(s);

    printf("%s\n", s);

    return 0;    
}

void reverse(char s[]) {
    int end = 0;
    
    while (s[end] != '\0') {
        ++end;
    }
    --end;

    int start = 0;
    int temp = 0;

    while (start != end && start < end) {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        ++start;
        --end;
    }
    
}

int getline_(char line[], int length) {
    int c, i = 0;
    
    while (i < length && (c = getchar()) != EOF && c != '\n') {
        line[i] = c;
        ++i;
    }
    
    line[i] = '\0';

    if (c == EOF) {
        return -1;
    } 
    return i;
}
