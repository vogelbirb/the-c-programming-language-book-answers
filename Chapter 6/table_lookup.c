#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// For getch
#include "common.h"
#include <stdbool.h>

struct nlist {          /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; /* found */
        }
    }
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {                    /* already there */
        free((void *)np->defn); /*free previous defn */
    }
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

int undef(char *name) {
    struct nlist *entry = lookup(name);
    if (entry == NULL) {
        return -1;
    }
    struct nlist *preceding = hashtab[hash(name)];
    while (preceding->next != entry->next && preceding->next != NULL) {
        preceding = preceding->next;
    }
    // `name` is the fist entry
    if (preceding == entry) {
        hashtab[hash(name)] = entry->next;
    }
    preceding->next = entry->next;
    free(entry);
    return 0;
}

// Modes are sequential, only to be used for define for now
enum reading_mode {
    NORMAL = 0,
    DIRECTIVE = 1,
    NAME = 2,
    DEFINITION = 3,
};

enum directive_type {
    NONE,
    DEFINE,
};

static inline char peek() {
    int c = getch();
    ungetch(c);
    return c;
}

// Defines MUST be null terminated
// Saves defines to lookup table from stdin
// Vunerable to buffer overflows
#define MAX_DIRECTIVE_LEN 100
#define DEF_BUF_LEN 1000
void process_directives() {
    // Could all be combined into a struct with useful methods
    enum reading_mode mode = NORMAL;
    char directive[MAX_DIRECTIVE_LEN] = {0};
    char *dp = directive;

    enum directive_type directive_type = NONE;
    bool read_next = false;

    char name[DEF_BUF_LEN] = {0};
    char *np = name;
    char definition[DEF_BUF_LEN] = {0};
    char *defp = definition;

    int c;
    while ((c = getch()) != EOF) {
        switch (c) {
        case '#':
            if (mode == NORMAL) {
                mode = DIRECTIVE;
            }
            break;
        case '\\':
            if (mode == DEFINITION && directive_type == DEFINE && peek() == '\n') {
                read_next = true;
                getch();
            }
            break;
        case '\n':
            if (mode == DEFINITION && directive_type == DEFINE && !read_next) {
                directive_type = NONE;
                mode = NORMAL;
                *defp = '\0';
                defp = definition;
                install(name, definition);
            }
            read_next = false;
            break;
        case ' ':
            if (mode > NORMAL) {
                if (directive_type == NONE) {
                    *dp = '\0';
                    dp = directive;
                    if (strcmp(directive, "#define") == 0) {
                        directive_type = DEFINE;
                    }
                }
                if (directive_type == DEFINE && mode == NAME) {
                    *np = '\0';
                    np = name;
                }
                if (mode != DEFINITION) {
                    mode++;
                }
                continue;
            }
            break;
        }

        switch (mode) {
        case DIRECTIVE:
            *dp++ = c;
            break;
        case NAME:
            *np++ = c;
            break;
        case DEFINITION:
            *defp++ = c;
            break;
        case NORMAL:
            break;
        }
    }
}

int main(void) {
    process_directives();
    struct nlist *secret = lookup("SECRET");
    if (secret != NULL) {
        printf("SECRET: %s\n", secret->defn);
    }
    return 0;
}