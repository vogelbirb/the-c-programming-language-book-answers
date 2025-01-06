#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    const char *prog = argv[0];

    int c, except = 0, number = 0, found = 0, label = 1;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c) {
            case 'x':
                except = 1;
                break;
            // Hide file labels
            case 'L':
                label = 0;
                break;
            case 'n':
                number = 1;
                except = 0; // Imcompatible with -x
                break;
            default:
                fprintf(stderr, "%s: illegal option %c\n", prog, c);
                argc  = 0;
                found = -1;
                break;
            }

    if (argc < 1) {
        printf("Usage: %s -x -n pattern [file...]\n", prog);
    } else {
        // argc and argv go crazy
        
        const char *pattern = *argv++;
        char        line[MAXLINE];
        const bool  file_stream = argc > 1;
        FILE       *stream      = stdin;
        while (argc >= 1) {
            long lineno = 0;
            if (file_stream) {
                stream = fopen(*argv, "r");
                if (label) {
                    printf("%s:\n", *argv);
                }
                argc--;
                if (stream == NULL) {
                    fprintf(stderr, "%s: failed to open %s\n", prog, *argv);
                    argc--;
                    argv++;
                    continue;
                }
            }
            while (fgets(line, MAXLINE, stream) != NULL) {
                // Removes newline so the line is displayed with a newline regardless if it's the last line or not
                char *newline = strchr(line, '\n');
                if (newline != NULL) {
                    *newline = '\0';
                }
                
                lineno++;
                if ((strstr(line, pattern) != NULL) != except) {
                    if (number) {
                        printf("%ld:", lineno);
                    }
                    printf("%s\n", line);
                    found++;
                }
            }
            argv++;
            if (file_stream) {
                fclose(stream);
            } else {
                argc--;
            }
        }
    }
    return found;
}