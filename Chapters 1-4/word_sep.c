#include <stdio.h>
#include <stdbool.h>

int main() {
    bool is_word = false; 
    // Used to wrap words to newlines
    bool prev_char_is_word = false;
    int c = '\0';

    while ((c = getchar()) != EOF) {
        if ((is_word = c != ' ' && c != '\n' && c != '\t')) {
            putchar(c);
        } else {
            if (prev_char_is_word) {
                putchar('\n');
            }
        }
        prev_char_is_word = is_word;
    }
    return 0;
}
