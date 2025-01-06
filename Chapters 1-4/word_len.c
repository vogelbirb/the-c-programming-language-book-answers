#include <stdio.h>
#include <stdbool.h>

#define MAX_WORD_LEN 15

bool is_whitespace(char c);

int main() {
    int c;
    int word_lengths[MAX_WORD_LEN] = {0};
    int word_len = 0;
    bool inside_word = false;

    while((c = getchar()) != EOF) {
        if (!is_whitespace(c)) {
            ++word_len;
        } else {
            if (word_len < MAX_WORD_LEN) {
                ++word_lengths[word_len - 1];
            } else {
                ++word_lengths[MAX_WORD_LEN - 1];
            }
            
            inside_word = false;
            word_len = 0;
        }
    }
    for (int i = 0; i < MAX_WORD_LEN; ++i) {
        printf("%4d", i + 1);
        if (i == MAX_WORD_LEN - 1) {
            printf("+ ");
        } else {
            printf("  ");
        }
        for (int j = 0; j < word_lengths[i]; ++j) {
            printf("=");
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
bool is_whitespace(char c) {
    return c == '\t' || c == ' ' || c == '\n';
}

