#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

int htoi(char s[]);

int main() {
    char hex[] = "0xFF";
    printf("%s = %i\n", hex, htoi(hex));
}

int htoi(char s[]) {
    int len = 0;
    while (s[len] != '\0') {
        ++len;
    }
    if (len == 0) {
        return -1;
    }
     
     
    int n = 0;
    int base = 1;
    bool has_0x = false;
    if (len > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        has_0x = true;
    }
    for (int i = len - 1; i >= (has_0x ? 2 : 0); --i) {
        int digit;
        if (isdigit(s[i])) {
            digit = s[i] - '0';
        } else {
            if (s[i] >= 'A' && s[i] <= 'F') {
                digit = s[i] - 'A' + 10;
            } else if (s[i] >= 'a' && s[i] <= 'f') {
                digit = s[i] - 'a' + 10;
            } else {
                return -1;
            }
        }
        n += base * digit;
        base *= 16;
    }
    return n;
}