#include <stdio.h>
#include <stdbool.h>
// strncpy, strncat, and strncmp
// char *strncpy(s,ct,n) copy at most n characters of string ct to s; return s. Pad with '\0''s if ct has fewer than n characters.
// char *strncat(s,ct,n) concatenate at most n characters of string ct to string s, terminate s with '\0'; return s.
// int strncmp(cs,ct,n) compare at most n characters of string cs to string ct; return <0 if cs<ct, 0 if cs==ct, or >0 if cs>ct.
/* getline: get line into s, return length */

int getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c=getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }
    if (c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int strncmp(const char *cs, const char *ct, const size_t n) {
    for (size_t i = 0; *cs == *ct && i < n; i++, cs++, ct++) {
        if (*cs == '\0') {
            return 0;
        }
    }
    return *cs - *ct;
}

char *strncat(char *s, const char *ct, const size_t n) {
    char *start = s;
    while (*++s)
        ;
    for (size_t i = 0; i < n; i++, s++, ct++) {
        *s = *ct;
    }
    *s = '\0';
    return start;
}

char *strncpy(char *s, const char *ct, const size_t n) {
    char *start = s;
    for (size_t i = 0; i < n; i++, s++, ct++) {
        *s = *ct;
    }
    return start; 
}

size_t strlen(const char *s) {
    size_t i = 0;
    while (*s++) {
        i++;
    }
    return i;
}

// Assumes there is enough space and s != t
char *strcat(char *s, const char *t) {
    char *start = s;
    while (*++s)
        ;
    while (*t) {
        *s++ = *t++;
    }
    *s = '\0';
    return start;
}

bool strend(const char *s, const char *t) {
    // Thanks ChatGPT I didn't notice
    if (strlen(t) > strlen(s)) {
        return 0;  // If t is longer than s, it can't match at the end
    }

    s = s + strlen(s) - strlen(t);
    do {
        if (*s != *t) {
            return 0;
        }
    } while (*++s && *++t);
    return 1;
}

int main() {
    char str1[100] = "Hello, ";
    const char *str2 = "world!";
    const char *str3 = "Hello, birds!";
    
    printf("str1: %s\n", str1);
    printf("str1: %s\n", strcat(str1, str2));
    
    printf("strlen is %lu\n", strlen(str1));
    
    str1[strlen(str1) - 1] = '?';
    printf("strend is %i\n", strend(str1, str2));

    printf("strncpy is %s\n", strncpy(str1, str3, strlen(str3)));

    printf("strncat is %s\n", strncat(str1, str3, strlen(str3)));
    printf("%s terminated\n", (str1[strlen(str1)] == 0) ? "is" : "is not");

    printf("str1: %s\n", str1);
    printf("str3: %s\n", str3);
    str1[7] = 'a';
    printf("str3[5]: %c\n", str3[7]);
    printf("strncopy is %i\n", strncmp(str1, str3, strlen(str3)));

    return 0;
}