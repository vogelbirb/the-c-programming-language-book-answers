#include <stdio.h>
#include <limits.h>

int main() {
    printf("unsigned char min is %i, max is %i\n", 0, UCHAR_MAX);
    printf("unsigned short min is %i, max is %u\n", 0, USHRT_MAX);
    printf("unsigned int min is %i, max is %u\n", 0, UINT_MAX);
    printf("unsigned long min is %i, max is %lu\n", 0, ULONG_MAX);
    printf("signed char min is %i, max is %i\n", SCHAR_MIN, SCHAR_MAX);
    printf("signed short min is %i, max is %i\n", SHRT_MIN, SHRT_MAX);
    printf("signed int min is %i, max is %i\n", INT_MIN, INT_MAX);
    printf("signed long min is %li, max is %li\n", LONG_MIN, LONG_MAX);
    printf("%c", '\377');
    return 0;
}