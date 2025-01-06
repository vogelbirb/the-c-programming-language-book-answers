#include <stdio.h>

int main() {
    char c = '\0';
    long spaces, newlines, tabs;
    spaces = newlines = tabs = 0;
    while ((c = getchar()) != EOF) {
        switch (c) {
            case ' ':
                ++spaces; 
            case '\n':
                ++newlines;
            case '\t':
                ++tabs;
        }
    }
    printf("Spaces: %ld, Newlines: %ld, Tabs: %ld\n", spaces, newlines, tabs);
    return 0;
}