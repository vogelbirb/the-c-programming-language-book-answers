#include <stdio.h>
#include <limits.h>

int setbits(unsigned x, unsigned pos, unsigned n, unsigned y);
int invert(unsigned x, unsigned n, unsigned pos);
int rightrot(int x, int n);
int bitcount(unsigned x);

int main() {
    unsigned int x = 0b10101001;
    // Should become 0b10101110;
    unsigned int y = 0b00001111;

    printf("setbits of %u = %u\n", x, setbits(x, 5, 3, y));
    x = 0b10101010;
    printf("invert of %u = %u\n", x, invert(x, 3, 1));
    
    printf("right rot of %u = %i\n", 0b1010, rightrot(-10, 2));
    
    x = INT_MIN;
    printf("%i has %i 1's\n", INT_MIN, bitcount(INT_MIN));
    
    return 0;
}

// y's bit length must be equal to pos - n
int setbits(unsigned x, unsigned pos, unsigned n, unsigned y) {
    return (x | (
        (y & ~(~0 << n)) << (pos - n)
    ));
}

// Could have used XOR bruh
int invert(unsigned x, unsigned n, unsigned pos) {
    const int MASK = ~(((~0 << (n)))) << pos;

    return (
        // x with section bits set to zero
        (~MASK & x) |
        // inversed section value
        ~(
            // section value
            (x & MASK) |
            // an inverse mask of the section
            (~MASK)
    ));
}

int rightrot(int x, int n) {
    // unsigned to prevent arithmetic shifts
    return (int)((unsigned)x >> n | (unsigned)x << (32 - n));
}

int bitcount(unsigned x) {
    int count = 0;
    while (x != 0) {
        x &= (x - 1);
        count++; 
    }
    return count;
}