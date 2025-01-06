#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINES 5000
#define MAXFIELDS 10
#define MAXLEN 1000 /* max length of any input line */

bool numeric = false;
bool reverse = false; 
bool fold = false;
bool directory = false;
bool debug = false;
int field = 0;

// escape_non_printable + display_array by CHATGPT

// Function to escape non-printable characters in a string
void escape_non_printable(char *str) {
    // Iterate through each character of the string
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isprint(str[i])) {
            // If it's a non-printable character, escape it
            switch (str[i]) {
                case '\n': printf("\\n"); break;
                case '\t': printf("\\t"); break;
                case '\r': printf("\\r"); break;
                case '\b': printf("\\b"); break;
                default: printf("\\x%02x", (unsigned char)str[i]); break;  // Hexadecimal escape for other non-printable chars
            }
        } else {
            // If it's printable, just print the character as is
            putchar(str[i]);
        }
    }
}

// Function to display a 2D array of strings
void display_array(char *arr[][MAXFIELDS], int num_rows) {
    // Iterate through the array (rows)
    for (int i = 0; i < num_rows; i++) {
        // Iterate through each column in the current row
        for (int j = 0; j < MAXFIELDS; j++) {
            // Check if the pointer is not NULL
            if (arr[i][j] != NULL) {
                escape_non_printable(arr[i][j]);  // Escape non-printable characters
            } else {
                printf("(null)");  // Print (null) if the pointer is NULL
            }
            printf("\t");  // Add a tab between fields
        }
        printf("\n");  // Newline after each row
    }
}

// Workaround for files with no terminating newline
bool will_eof = false;

size_t _getline(char *s, const int lim) {
    if (will_eof) {
        return -1;
    }
    char *s_start = s;
    
    size_t count = 0;
    bool eof = false;
    while ((*s = getchar()) != EOF && *s != '\n' && count < lim) {
        count++;
        s++;
    }
    eof = *s == EOF;

    // EOF is also checked here because I'm too lazy to fix readlines function (written by K&R, not me)
    if (*s == '\n' || *s == EOF) {
        *s++ = '\n';
        count++;
    } 
    *s = '\0';

    will_eof = eof;
    return count;
}

/* max #lines to be sorted */
/* pointers to text lines */
/* _qsort: sort v[left]...v[right] into increasing order */
// fields[i] corresponds to all fields
void swap(void *v[], int i, int j) {
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void swap_rows(char *arr[][MAXFIELDS], int row1, int row2) {
    // Swap the rows by swapping the pointers to the rows
    char *temp[MAXFIELDS];
    for (int i = 0; i < MAXFIELDS; i++) {
        temp[i] = arr[row1][i];
        arr[row1][i] = arr[row2][i];
        arr[row2][i] = temp[i];
    }
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

#define BUFF_LEN 10000
static char buff[BUFF_LEN] = {0};
static char *buff_ptr = buff;

char *alloc(const size_t len) {
    if(BUFF_LEN - (buff_ptr - buff) >= len) {
        buff_ptr += len;
        return buff_ptr - len;  
    } else {
        return NULL;
    }
}

void linerev(char *s[], const size_t len) {
    char **p1 = &s[0];
    char **p2 = &s[len - 1];
    size_t len_p1;
    size_t len_p2;
    
    while (p2 > p1) {
        char *temp = *p1;
        *p1 = *p2;
        *p2 = temp; 

        p1++;
        p2--;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    // TODO: Fix function to save fields correctly
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = _getline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void _qsort(void *v[], int left, int right,
int (*comp)(const void *, const void *), char *fields[][MAXFIELDS])
{
    bool field_sort = fields != NULL;

    int i, last;
    if (left >= right) /* do nothing if array contains */
        return;        /* fewer than two elements */

    swap(v, left, (left + right)/2);
    if (field_sort) {
        swap_rows(fields, left, (left + right) / 2);
    }
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(field_sort ? fields[i][field - 1] : v[i], field_sort ? fields[left][field - 1] : v[left]) < 0) {
            swap(v, ++last, i);
            if (field_sort) {
                swap_rows(fields, last, i);
            }
        }
    }
    swap(v, left, last);
    if (field_sort) {
        swap_rows(fields, left, last);
    }
    _qsort(v, left, last-1, comp, fields);
    _qsort(v, last+1, right, comp, fields);
}

// Quirk: debug flag starts working only after it is parsed, so other flags that appeared before might not be logged. Could be fixed but don't feel like typing it all out.
int parse_args(const int argc, const char **argv) {
    if (argc < 2) {
        return 0;
    }

    while (*++argv) {
        const char *flags = *argv;
        
        if (*flags != '-') {
            return -1;
        }

        while (*++flags) {
            switch (*flags) {
                // Display debug info
                case 'x':
                    debug = true;
                    break;
                // Field searching
                case 's':
                    field = -1;
                    break;
                // Numeric order
                case 'n':
                    numeric = true;
                    break;
                // Reverse
                case 'r':
                    reverse = true;
                    break;
                // Ignore case
                case 'f':
                    fold = true;
                    break;
                // Ignore symbols
                case 'd':
                    directory = true;
                    break;
                default:
                    return -1;
            }
            if (debug) {
                printf("flag: %c\n", *flags);
            }
        }

        if (field < 0) {
            const char *val = *(++argv);
            if (debug) {
                printf("      s = %s\n", val);
            }
            if (!val) {
                return -1;
            }
            int parsed_val = (int)atof(val);
            if (parsed_val == 0) {
                return -1;
            }
            field = (int)atof(val);
        }

    }
    return 0;
}

int strcmp_w_opts(const char *s1, const char *s2) {
    size_t len_s1 = strlen(s1);
    size_t len_s2 = strlen(s2);
    
    char s1_cpy[len_s1];
    char s2_cpy[len_s2];
    strcpy(s1_cpy, s1);
    strcpy(s2_cpy, s2);

    if (directory) {
        char *p1 = s1_cpy;
        char *p2 = s2_cpy;
        while (*p1 && *p2) {
            if (!isalnum(*p1) && !isspace(*p1)) {
                *p1 = ' ';
                *p2 = ' ';
            } else if (!isalnum(*p2) && isspace(*p2)) {
                *p1 = ' ';
                *p2 = ' ';
            }
            p1++;
            p2++;
        }
    }
    if (fold) {
        char *p1 = s1_cpy;
        char *p2 = s2_cpy;
        while (*p1) {
            *p1 = tolower(*p1);
            p1++;
        }
        while (*p2) {
            *p2 = tolower(*p2);
            p2++;
        }
    }
    
    return strcmp(fold || directory ? s1_cpy : s1, fold || directory ? s2_cpy : s2);
}


size_t split(char *s, char **t, const char c) {
    size_t count = 1;
    
    char *ps = s;
    while (*s) {
        if (*s == c) {
            size_t len = s - ps;
            // Leaks/wastes/duplicates memory, I know
            char *temp = alloc(len + 1);
            if (*temp == -1) {
                printf("Error: out of allocator memory. Seg fault ahead lol");
            }
            strncpy(temp, ps, len);
            temp += len;
            *temp = '\0';
            count++;
            *t++ = temp - len;
            ps = s + 1; 
        }
        s++;
    }
    *t++ = ps; 
    return count;
}

/* sort input lines */
int main(const int argc, const char **argv)
{
    char *lines[MAXLINES];
    /* number of input lines read */
    int nlines;
    
    if (parse_args(argc, argv) == -1) {
        printf("Usage: sort [-xdfrn, -s NUMBER]\n");
        return 1;
    }

    if ((nlines = readlines(lines, MAXLINES)) >= 0) {
         char *fields[nlines][MAXFIELDS];
        for (int i = 0; i < nlines; i++) {
            for (int k = 0; k < MAXFIELDS; k++) {
                fields[i][k] = NULL;
            }
        }
        
        if (field > 0) {
            size_t max = 1;
            size_t split_out = 0;
            for (int i = 0; i < nlines; i++) {
                if ((split_out = split(lines[i], fields[i], ',')) > max) {
                    max = split_out;
                }
            }

            if (field > max) {
                printf("Error: invalid field\n");
                return 1;
            }
        }
        if (debug) {
            display_array(fields, nlines);
        }
        
        int (*cmp_fn)(const void*, const void*) = (int (*)(const void*, const void*)) (numeric ? numcmp : strcmp_w_opts);
        _qsort((void**) lines, 0, nlines - 1, cmp_fn, field > 0 ? fields : NULL);
        
        if (reverse) {
            linerev(lines, nlines);
        }
        writelines(lines, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}
