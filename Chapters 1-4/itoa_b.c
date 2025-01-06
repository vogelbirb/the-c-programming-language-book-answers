#include <stdio.h>
#include <string.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);
void itob(int n, char s[], int b);
void itoa_padded(int n, char s[], int width);

int main() {
    char s[] = "hello, world!";
    char v[100] = "";

    itoa(INT_MAX, v);
    printf("%s\n", v);
    
    itob(-36, v, 36);
    printf("%s\n", v);
    
    itoa_padded(-69, v, 4);
    printf("PADDED:%s\n", v);
    printf("len of v = %i\n", strlen(v));
    return 0;
}

// Handles INT_MIN
void itoa(int n, char s[]) {
    int i = 0, sign;

    if ((sign = n) < 0) {
        n = -(n == INT_MIN) ? n - 1 : n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0) {
        s[i++] = '-';
    }
    
    if (sign == INT_MIN) {
        s[0] += 1;
    }
    
    s[i] = '\0';
    reverse(s);
}

// Does not handle INT_MIN
// width = minimum string width
void itoa_padded(int n, char s[], int width) {
    int i = 0, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0) {
        s[i++] = '-';
    }
    
    for (int j = 0; j <= width - i; j++) {
        s[i++] = ' ';
    }
    
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[]) {
    // A bit inefficient because of strlen
    char temp;
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

// Up to base 36, does not handle INT_MIN
void itob(int n, char s[], int base) {
    int i = 0, sign;

    if ((sign = n) < 0) {
        n = -n;
    }
    i = 0;
    do {
        s[i++] = n % base + ((n % base > 9) ? 'A' - 10 : '0');
    } while ((n /= base) > 0);
    
    if (sign < 0) {
        s[i++] = '-';
    }
    
    s[i] = '\0';
    reverse(s);
    
}