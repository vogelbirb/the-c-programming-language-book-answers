#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(const int argc, const char *argv[]) /* lower: convert input to lower case*/
{
    const char *mode = (argc > 1) ? argv[1] : "lower";
    
    int c;
    while ((c = getchar()) != EOF) {
        putchar((strcmp(mode, "upper") == 0) ? toupper(c) : tolower(c));
    }
    return 0;
}
