#include <stdio.h>

int any(char s1[], char s2[]);

int main() {
    char str1[] = "Hello, Yam! Bye, Zack!";
    char str2[] = "ZBY";

    char i = any(str1, str2);
    printf("In the context of the string \"%s\", either one of the characters present on the string \"%s\" are first seen at position %i, where the character \"%c\" stands.\n", str1, str2, i, str1[i]);

    return 0;
}

int any(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0') {
        for (int j = 0; s2[j] != '\0'; j++) {
            if (s2[j] == s1[i]) {
                return i;
                break;
            }
        }
        i++;
    }
    return -1;
}