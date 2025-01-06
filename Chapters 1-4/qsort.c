#include <stdio.h>

void sort(int arr[], const int left, const int right);
void disp_array(const int arr[], const int len);
void swap(int arr[], int a, int b);

int main() {
    int arr[10] = {30, 10, 20, 50, 60, 70, 100, 90, 45, 35};
    disp_array(arr, 10);
    sort(arr, 0, 9);
    disp_array(arr, 10);
    return 0;
}

void sort(int arr[], const int left, const int right) {
    if (left >= right) {
        return;
    }
    int i = left - 1;
    int j = left;
    int pivot = right;

    while (j <= pivot) {
        if (arr[j] < arr[pivot]) {
            i++;
            swap(arr, j, i);
        }
        j++;
    }
    i++;
    swap(arr, i, pivot);
    pivot = i;

    sort(arr, left, pivot - 1);
    sort(arr, pivot + 1, right);
}
void disp_array(const int arr[], const int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%s%i", i > 0 ? ", " : "", arr[i]);
    }
    printf("]\n");
}

void swap(int arr[], const int a, const int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}