#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// _getline
// alloc
#include "../Chapter

#define MAXLINE 100
#define USAGE "Usage: tail [-n number > 0]\n"

// Takes arguments from user. Returns `-1` for invalid usage and keeps arguments unchaged for no arguments.
int parse_args(const char *argv[], const int argc, size_t *nlines) {
    if (argc <= 1) {
        return 0;
    } else if (argc < 3) {
        return -1;
    }

    if (**++argv != '-') {
        return -1;
    }
    
    char flag = *((*argv) + 1);
    const char *value = *++argv;
    switch (flag) {
        case 'n': {
            double parsed_value = atof(value);
            if (parsed_value != 0) {
                *nlines = parsed_value;
            } else {
                return -1;
            }
            break;
        }
        default:
            return -1;
    } 
    return 0;
}

// Saves all lines until `EOF`. Returns `-1` for not enough buffer space, otherwise returns line count.
size_t getlines(char *s[]) {
    char *line;
    bool is_eof = false; 

    int count = 0;
    while (!is_eof) {
        line = alloc(MAXLINE);
        if (!line) {
            return -1;
        }
        *line = '\0';
        
        is_eof = _getline(line, MAXLINE) == -1;

        *s++ = line;
        count++;
    }
    return count;
}

int main(const int argc, const char *argv[]) {
    size_t nlines = 10; 

    if (parse_args(argv, argc, &nlines) == -1) {
        printf(USAGE);
        return 1;
    }

    char *lines[MAXLINE] = {NULL};
    size_t len = getlines(lines);
    if (len == -1) {
        printf("Error: line buffer ran out of space.\n");
        return 1;
    }

    if (nlines > len) {
        nlines = len;
    }
    while (nlines > 0) {
        printf("%s", lines[len - nlines]);
        nlines--;
    }
    
    return 0;
}
