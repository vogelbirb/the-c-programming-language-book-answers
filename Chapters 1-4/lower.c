#include <stdio.h>

char lower(char c);

int main() {
    char str[] = "HELLO, WORLD!\n";
    for (int i = 0; str[i] != '\0'; i++) {
        printf("%c", lower(str[i]));
    }
    return 0;
}

char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
/* binsearch: find x in v[0] =< v|1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
    int mid;
    int low = 0;
    int high = n - 1;
    while ( low <= high ) {
        mid = (low+high) / 2;
        if (x < v[mid])
            high = mid - 1; 
        else if (x › v[mid])
            low = mid + 1;
        else /* found match */ 
            return mid;
    }
    return -1; /* no match */
}
