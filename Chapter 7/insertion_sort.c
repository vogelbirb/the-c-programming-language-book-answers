#include <stdio.h>

#define LEN(arr) sizeof arr / sizeof arr[0]

typedef int arr_type;

void insertion_sort(arr_type arr[], const size_t len) {
    arr_type temp;
    for (size_t i = 1; i < len; i++) {
        temp = arr[i];
        for (size_t j = i - 1; j >= 0; j--) {
            if (arr[j] > temp) {
                arr[j + 1] = arr[j];
                arr[j] = temp;
            } else {
                arr[j + 1] = temp;
                break;
            }
        }
    }
}

void disp_array(arr_type *arr, const size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%i%s", arr[i], (i + 1 < len) ? ", " : "");
    }
    printf("]\n");
}

int main(void) {
    arr_type arr[] = {4, 3, 2, 7, 8};

    disp_array(arr, LEN(arr));
    insertion_sort(arr, LEN(arr));
    disp_array(arr, LEN(arr));

    return 0;
}