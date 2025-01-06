#include <stdio.h>

int main() {
    char secret[] = "this is a secret string!";
    char secret2[] = "other secret string!";
    char secret3[] = "another secret string!";
    char secret4[] = "what???";

    for (int i = 0; i < 300; i++) {
        printf("%c", secret[i]);
    }
}