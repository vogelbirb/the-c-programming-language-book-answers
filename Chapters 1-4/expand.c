#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 100
#define MAX_CHARS 100

// Use this
enum MODE { DIGIT = 0, UPPERCASE = 1, LOWERCASE = 2}

void expand(const char s1[], char s2[]);
// For debugging purposes
void disp_array(int arr[], int len);

int main() {
    const char s1[STR_LEN] = "-f-g-k";
    char s2[STR_LEN]  = "";

    expand(s1, s2);
    printf("\"%s\" to \"%s\"\n", s1, s2);

    return 0;
}

// Tons of edge cases

// Expands shorthand notations like 'a-z', '3-5', or '-f-g-k' into their full form. Can contain leading or trailing dashes.
// WARNING: s1 must be either all digits or all letters, otherwise expect undefined behavior. 
void expand(const char s1[], char s2[]) {
    // Can't wait for pointers! Long ass book
    int bounds_ptr = 0;
    
    int bounds[MAX_CHARS] = {0};
    
    // 0 = digits, 1 = uppercase letters, 2 = lowercase letters
    // Could very well be an enum
    int mode = 0;
    
    for (int i = 0; s1[i] != '\0'; i++) {
        if (isalpha(s1[i])) {
            if (isupper(s1[i])) {
                mode = 1;
            } else {
                mode = 2;
            }
        }
        if (s1[i] != '-') {
            bounds[bounds_ptr++] = s1[i];
        }
    }

    // Leading
    if (s1[0] == '-') {
        for (int i = bounds_ptr - 1; i >= 0; i--) {
            bounds[i + 1] = bounds[i];
        }
        switch (mode) {
            case 0:
                bounds[0] = '0';
                break;
            case 1:
                bounds[0] = 'A';
                break;
            case 2:
                bounds[0] = 'a';
                break;
        }
        bounds_ptr++;
    }

    // Trailing
    if (s1[strlen(s1) - 1] == '-') {
        switch (mode) {
            case 0:
                bounds[bounds_ptr++] = '9';
                break;
            case 1:
                bounds[bounds_ptr++] = 'Z';
                break;
            case 2:
                bounds[bounds_ptr++] = 'z';
                break;
        }
    }

    int s2_ptr = 0;
    for (int i = 1; i <= bounds_ptr; i++) {
        for (int c = bounds[i - 1] + (/* Avoid duplicating entries, except when at the beginning */ (i > 1) ? 1 : 0); c <= bounds[i]; c++) {
            s2[s2_ptr++] = c;
        }
    }
    s2[s2_ptr++] = '\0';
}

void disp_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%i", i > 0 ? ", " : "", arr[i]);
    }
    printf("]\n");
}