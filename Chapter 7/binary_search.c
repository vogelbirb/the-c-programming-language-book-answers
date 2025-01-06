#include <stdio.h>

int *binary_search(const int arr[], const size_t len, const int val) {
    // [1, 2, 3, 4]
    const int *min = arr;
    const int *max = arr + len - 1;
    const int *mid; 
    
    while (min <= max) {
        mid = min + (max - min) / 2;
        if (val > *mid) {
            min = mid + 1;
        } else if (val < *mid) {
            max = mid - 1;
        } else {
            return (int *)mid;
        }
    }
    return NULL;
}

int main(void) {
    const int arr[] = {2,4,5,7,8,9};
    
    const int *val = binary_search(arr, sizeof arr / sizeof arr[0], 10);
    printf("found: %i\n", (val == NULL) ? -1 : *val);

    return 0;
}