#include <stdio.h>

#define V_LEN 6

void bubble_sort(int v[], int len);
void insertion_sort(int v[], int len);
void disp_array(int arr[], int len);

int main() {
    int v[V_LEN] = {-5,9,7,5,-10,-9};
     
    printf("Before Sort:\t");
    disp_array(v, V_LEN);
    
    // bubble_sort(v, V_LEN);
    insertion_sort(v, V_LEN);

    printf("After Sort:\t");
    disp_array(v, V_LEN);
    
    return 0;
}

void bubble_sort(int v[], int len) {
    int temp;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - 1; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(int v[], int len) {
    int key;
    for (int i = 1; i < len; i++) {
        key = v[i];
        for (int j = i; j > 0; j--) {
            if (v[j - 1] > key) {
                v[j] = v[j - 1];
                // Run out of elements
                if (j == 1) {
                    v[0] = key;
                }
            } else {
                v[j] = key;
                break;
            }
        }
    }
}

void disp_array(int arr[], int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%i", i > 0 ? ", " : "", arr[i]);
    }
    printf("]\n");
}