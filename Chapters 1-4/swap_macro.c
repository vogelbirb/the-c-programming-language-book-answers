#include <stdio.h>

#define swap(t, x, y) { t temp = n1; n1 = n2; n2 = temp; }

int main() {
    int n1 = 6;
    int n2 = 3;
    printf("n1 = %i\n", n1);
    printf("n2 = %i\n", n2);
    swap(int, n1, n2);
    printf("n1 = %i\n", n1);
    printf("n2 = %i\n", n2);
    return 0;
}