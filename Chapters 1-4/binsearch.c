#include <stdio.h>

int binsearch(int x, int v[], int n);

int main() {
    // nums[5] = 9
    int nums[10] = {2,3,5,6,8,9,10,13,16,21};

    printf("%i\n", binsearch(9, nums, 10));

    return 0;
}

/* binsearch: find x in v[0] =< v|1] <= ... <= v[n - 1] */
int binsearch(int x, int v[], int n) {
    int mid;
    int low = 0;
    int high = n - 1;

    while (low <= high && v[mid] != x) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1; 
        // If it's not equal to or less than, then it's greater (something so trivial took me a while to figure out I don't know why)
        } else {
            low = mid + 1;
        }
    }

    if (v[mid] == x) {
        return mid;
    } else {
        return -1;
    }
}
