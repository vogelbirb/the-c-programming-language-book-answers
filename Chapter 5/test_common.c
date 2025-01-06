#include <stdio.h>
#include <string.h>
#include "common.h"

#define MAXLINE 1000

int main(void) {
    char line[MAXLINE] = "";
    printf("what is your name?: ");
    _getline(line, MAXLINE);
    
    // Remove newline
    line[strlen(line) - 1] = '\0';
    
    printf("Hello, %s!\n", line);
    return 0;
}
