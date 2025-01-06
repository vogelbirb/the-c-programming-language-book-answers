// TODO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
 
int itoa(int n, char s[]);
void reverse(char[], int, int);
void disp_array(int arr[], int len);
 
int main() {
    int n = -123;
    char s[100] = "";
    
    itoa(n, s);

    printf("%i = %s\n", n, s);
    
    printf("\t%s\n", s);
    reverse(s, 0, strlen(s) - 1);
    printf("\t%s\n", s);
    
    return 0;
}
 
// static solution
// only works once I think
// void itoa(int n, char s[])
// {
//     static int i = 0, calls = 0;
//     calls++;

//     if (n == 0) {
//         if (calls == 1) {
//             s[i++] = '0';
//             s[i] = '\0';
//         }
//         return;
//     }
    
//     int sign;
//     /* record sign */
//     if ((sign = n) < 0) {
//         n = -n; /* make n positive */
//     }

//     if (sign < 0) {
//         s[i++] = '-';
//     }
    

//     itoa(n / 10, s);
//     s[i++] = n % 10 + '0'; /* get next digit */
    
//     s[i] = '\0';
// }

// Does not work with INT_MIN.
// In fact, uses it as flag for the base case, along with zero.
int itoa(int n, char s[])
{
    int i = 0;
    
    if (n == INT_MIN) {
        s[i++] = '-';
        return 1;
    } else if (n == 0) {
        // Allows all of this to get overwritten if this is a base case, and not an explicit call to itoa(0, s[]).
        s[i] = '0';
        s[i + 1] = '\0';
        return 0;
    }

    i += itoa((n / 10 == 0) ? ((n < 0) ? INT_MIN : 0) : n / 10, s);
    s[i++] = abs(n) % 10 + '0';
     
    s[i] = '\0';
    
    return i;
}

/* reverse: reverse string s in place */
void reverse(char s[], int left, int right)
{
    if (left > right) {
        return;
    }
    int temp = s[left];
    s[left] = s[right];
    s[right] = temp;
    reverse(s, left + 1, right - 1);
}

void disp_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%i", i > 0 ? ", " : "", arr[i]);
    }
    printf("]\n");
}