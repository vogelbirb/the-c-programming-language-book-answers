#include <fcntl.h>
#include <string.h>
#include "syscalls.h"

#define EOF -1
#define stdin 0
#define stdout 1
#define stderr 2

int my_getc(const int fd) {
    char c;
    return (read(fd, &c, 1) == 1) ? (unsigned char) c : EOF;
}

void my_putc(const char c, const int fd) {
    write(fd, &c, 1);
}

void filecopy(const int fd1, const int fd2) {
    int c;
    while ((c = my_getc(fd1)) != EOF)
        my_putc(c, fd2);
}

int my_fopen(const char *name, int flags) {
    return open(name, flags);
}

void my_fclose(const int fd) {
    close(fd);
}

void fprint(const int fd, char *s) {
    while (*s) {
        // Buffering is kind of horrible
        my_putc(*s, fd);
        s++;
    }
}

const char *err_message = "cat: can't open ";

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[]) {
    int fd;
    if (argc == 1) /* no args; copy standard input */
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fd = my_fopen(*++argv, O_RDONLY)) == -1) {
                // Did you realize that my_fprint is called fprint instead of fprint"F"? This is the "f" part.
                char msg[strlen(err_message) + strlen(*argv) + 2]; // + \n + \0
                strcpy(msg, err_message);
                strcat(msg, *argv);
                strcat(msg, "\n");
                
                fprint(stderr, msg);
                return 1;
            } else {
                filecopy(fd, stdout);
                my_fclose(fd);
            }
    return 0;
}