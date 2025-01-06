#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_LEN 100
#define MAX_VARS_GROUP 100
#define BUFSIZE 100
/* buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0;

/* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)
/* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
// Imposes limitation to support only fixed list of simple types
char *types[] = {
    "bool", "char", "double", "float", "int",
};

struct tnode {
    char group[TOKEN_LEN];
    // Stack data structure
    // Could be something separate but for now this is enough
    // Would be crucial if this got more complex
    char variables[MAX_VARS_GROUP][TOKEN_LEN];
    size_t free_slot;
    struct tnode *left;
    struct tnode *right;
};

void insert_var(struct tnode *tree, const char variable[]) {
    strcpy(tree->variables[tree->free_slot], variable);
    tree->free_slot++;
}

struct tnode *init_tree() {
    struct tnode *tree = malloc(sizeof(struct tnode));
    for (size_t i = 0; i < TOKEN_LEN; i++) {
        tree->group[i] = 0;
    }
    for (size_t i = 0; i < MAX_VARS_GROUP; i++) {
        for (size_t j = 0; j < TOKEN_LEN; j++) {
            tree->variables[i][j] = 0;
        }
    }
    tree->left = NULL;
    tree->right = NULL;
    tree->free_slot = 0;
    return tree;
}

void print_tree(const struct tnode *tree) {
    if (tree != NULL) {
        print_tree(tree->left);
        printf("%s:\n", tree->group);
        for (size_t i = 0; i < MAX_VARS_GROUP; i++) {
            if (i < tree->free_slot) {
                printf("%s \t", tree->variables[i]);
            }
        }
        printf("\n");
        print_tree(tree->right);
    }
}

struct tnode *add_tree(struct tnode *tree, const char *variable_name, const size_t ident_len) {
    char ident[ident_len + 1];
    strncpy(ident, variable_name, ident_len);
    ident[ident_len] = '\0';

    if (tree == NULL) {
        struct tnode *tree = init_tree();

        strcpy(tree->group, ident);
        insert_var(tree, variable_name);

        return tree;
    }

    char tree_ident[ident_len + 1];
    strncpy(tree_ident, tree->group, ident_len);
    tree_ident[ident_len] = '\0';

    int cmp_result = strcmp(ident, tree_ident);
    if (cmp_result < 0) {
        if (tree->left == NULL) {
            tree->left = init_tree();
            strcpy(tree->left->group, ident);
            insert_var(tree->left, variable_name);
            return tree;
        }
        add_tree(tree->left, variable_name, ident_len);
    } else if (cmp_result > 0) {
        if (tree->right == NULL) {
            tree->right = init_tree();
            strcpy(tree->right->group, ident);
            insert_var(tree->right, variable_name);
            return tree;
        }
        add_tree(tree->right, variable_name, ident_len);
    } else {
        insert_var(tree, variable_name);
        return tree;
    }
    return tree;
}

// Returns true `c` is alphabetic, an underscore, and numeric if `first = false` AKA a valid name for a variable in C
bool is_valid_var(const char c, const bool first) { return first ? isalpha(c) : isalnum(c) || c == '_'; }

// Returns true `c` is alphabetic, an underscore (`_`), a double or single quote
// (`"`, `'`), a forward slash or asterisk (/, *), and numeric
bool is_valid(const char c) {
    return is_valid_var(c, false); // || c == '\'' || c == '"' || c == '/' || c == '*';
}

enum status {
    NONE,
    STRING,
    CHAR,
    MULTI_LINE,
    SINGLE_LINE,
    FINISHED,
};

enum token_type {
    SYMBOL = 1,
    COMMENT = 2,
    LITERAL = 3,
    WORD = 4,
    NEWLINE = 5,
};

// Flips from `new_val` to FINISHED and NONE to `new_val` and vice versa only if `val = NONE` or `val = new_val`
extern inline enum status flip(enum status val, enum status new_val) {
    return (val == new_val) ? FINISHED : (val == NONE) ? new_val : val;
}
extern inline char prev(const char *token, const size_t i) { return (i > 0) ? *(token - 1) : '\0'; }
extern inline char peek() {
    int c = getch();
    ungetch(c);
    return c;
}

// Sets `token` to next word with up to `len` characters. A token is a whole string/character literal, valid variable
// name, or a single symbol.
int get_token(char *token, const size_t len) {
    if (len < 1) {
        *token = '\0';
        return 0;
    }

    int c;
    while (isspace((c = getch())))
        ;
    *token = c;

    enum status status = NONE;
    enum token_type type = WORD;

    for (size_t i = 0; i < len && *token != EOF && status != FINISHED; i++, *++token = getch()) {
        switch (*token) {
        case '*':
            if (peek() == '/' && status == MULTI_LINE) {
                getch();
                *++token = '/';
                status = FINISHED;
            }
            break;
        case '/':
            if (peek() == '*' && status == NONE) {
                type = COMMENT;
                getch();
                *++token = '*';
                status = flip(status, MULTI_LINE);
            } else if (peek() == '/' && status == NONE) {
                type = COMMENT;
                getch();
                *++token = '/';
                status = flip(status, MULTI_LINE);
            }
            break;
        case '\'':
            if (prev(token, i) != '\\') {
                type = LITERAL;
                status = flip(status, CHAR);
            }
            break;
        case '\"':
            if (prev(token, i) != '\\') {
                type = LITERAL;
                status = flip(status, STRING);
            }
            break;
        }

        if (!is_valid(*token) && status == NONE) {
            if (i > 0) {
                ungetch(*token);
            } else {
                type = SYMBOL;
                *++token = getch();
                ungetch(*token);
            }
            break;
        }
    }

    if (status == FINISHED) {
        ungetch(*token);
    }
    bool eof = *token == EOF;
    *token = '\0';
    if (eof) {
        return -type;
    } else {
        return type;
    }
}

int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int main(const int argc, const char *argv[]) {
    size_t group_len = (argc > 1) ? *argv[1] - '0' : 6;

    char token[TOKEN_LEN] = {0};
    int type = 0;

    char prev_word[TOKEN_LEN] = {0};
    int prev_type = 0;
    struct tnode *v_tree = NULL;

    while ((type = get_token(token, TOKEN_LEN)) > 0) {
        const char *key = &prev_word[0];
        if (prev_type == WORD && type == WORD &&
            bsearch(&key, types, sizeof(types) / sizeof(types[0]), sizeof(types[0]),
                    compare_strings) != NULL) {
            v_tree = add_tree(v_tree, token, group_len);
        }
        strcpy(prev_word, token);
        prev_type = type;
    }
    printf("GROUPS\n");
    print_tree(v_tree);
    return 0;
}
