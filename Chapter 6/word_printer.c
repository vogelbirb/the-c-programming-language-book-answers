#include "common.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TOKEN_LEN 100
#define LINE_LEN 10000
#define MAXLINES 100

// clang-format off
const char *noise[] = {
    // Articles
    "the", "a", "an",

    // Conjunctions
    "and", "or", "but", "so", "yet", "for", "nor",

    // Prepositions
    "in", "on", "at", "to", "of", "by", "with", "about", "as", "into", "onto", "upon", "through",
    "between", "among", "across", "over", "under", "above", "below", "around", "near",

    // Pronouns
    "i", "you", "he", "she", "it", "we", "they",
    "me", "him", "her", "us", "them",
    "my", "your", "his", "her", "its", "our", "their",
    "mine", "yours", "theirs",
    "myself", "yourself", "himself", "herself", "itself", "ourselves", "yourselves", "themselves",

    // Auxiliary Verbs
    "be", "is", "are", "was", "were", "am", "been", "being",
    "have", "has", "had",
    "do", "does", "did",
    "will", "shall", "would", "should", "can", "could", "may", "might", "must",

    // Adverbs
    "very", "too", "also", "not", "only", "just", "so", "well", "then", "now", "always", "never", "often", "sometimes",

    // Others
    "there", "here", "this", "that", "these", "those", "some", "any", "all", "few", "many", "much", "each", "every", "none",
    "which", "who", "whom", "whose", "what", "where", "when", "why", "how"
};
const size_t noise_count = sizeof(noise) / sizeof(noise[0]);
// clang-format on

int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

char *to_lower_cpy(char *t, const char *s) {
    char *start = t;
    while (*s) {
        *t = tolower(*s);
        s++;
        t++;
    }
    return start;
}

struct tnode {
    char word[TOKEN_LEN];
    // Kind of a stack I guess, a hash set would be a litle better for duplicates in lines for large datasets
    int lines[MAXLINES];
    size_t count;
    struct tnode *left;
    struct tnode *right;
};

void print_tree(const struct tnode *tree) {
    if (tree != NULL) {
        print_tree(tree->left);
        printf("%s:\t", tree->word);
        for (size_t i = 0; i < tree->count; i++) {
            printf("%s%i", (i > 0) ? ", " : "", tree->lines[i]);
        }
        printf("\n");
        print_tree(tree->right);
    }
}

// If `word` is not equal to current value, it will be overwritten
void insert_word(struct tnode *tree, const char *word, const size_t line) {
    if (tree->count > MAXLINES) {
        printf("Error: out of space for lines");
        exit(1);
    }
    strncpy(tree->word, word, TOKEN_LEN - 1);
    tree->word[TOKEN_LEN - 1] = '\0';
    tree->lines[tree->count] = line;
    tree->count++;
}

void free_tree(struct tnode *tree) {
    if (tree == NULL)
        return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

struct tnode *init_tree() {
    struct tnode *tree = malloc(sizeof(struct tnode));
    tree->left = NULL;
    tree->right = NULL;
    tree->count = 0;
    return tree;
}

struct tnode *add_tree(struct tnode *tree, const char *word, const size_t line) {
    if (tree == NULL) {
        tree = init_tree();
        insert_word(tree, word, line);
        return tree;
    }

    int cmp_result = strcmp(tree->word, word);
    if (cmp_result < 0) {
        tree->left = add_tree(tree->left, word, line);
    } else if (cmp_result > 0) {
        tree->right = add_tree(tree->right, word, line);
    } else {
        insert_word(tree, word, line);
    }
    return tree;
}

struct tnode *process_words() {
    // For future use to print out full line
    char line[LINE_LEN] = {0};
    struct tnode *tree = NULL;
    char token[TOKEN_LEN] = {0};
    int out = 1;
    int line_num = 1;
    *line = '\0';
    while (out > 0) {
        out = get_token(token, TOKEN_LEN);

        char lowercase_cpy[TOKEN_LEN] = {0};
        to_lower_cpy(lowercase_cpy, token);

        char *key = lowercase_cpy;
        if (strcmp(token, "\n") == 0) {
            line_num++;
        }
        if (bsearch(&key, noise, noise_count, sizeof noise[0], compare_strings) == NULL) {
            if (abs(out) == WORD) {
                tree = add_tree(tree, token, line_num);
            }
            strcat(line, token);
            if (strcmp(token, "\n") != 0) {
                strcat(line, " ");
            }
        }
    };
    return tree;
}

int main(void) {
    qsort(noise, noise_count, sizeof noise[0], compare_strings);
    struct tnode *tree = process_words();
    if (tree != NULL) {
        print_tree(tree);
    }
    free_tree(tree);
}
