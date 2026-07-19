#include <stdio.h>

#define DEFAULT_ORDER 0
#define REVERSE_ORDER 1

static size_t find_element(const int *arr, size_t size, unsigned char order) {
    size_t sindex = 0;

    if (order) {
        for (size_t i = 1; i < size; i++) {
            if (arr[sindex] < arr[i]) {
                sindex = i;
            }
        }
    } else {
        for (size_t i = 1; i < size; i++) {
            if (arr[sindex] > arr[i]) {
                sindex = i;
            }
        }
    }
    return sindex;
}

/*static size_t find_smallest(int *arr, size_t size) {

}*/

int selectionsort(int *arr, size_t size, unsigned char order) {
    if (arr == NULL || order > 1) {
        return -1;
    }
    if (size <= 1) {
        return 0;
    }
    for (size_t i = 0; i < size - 1; i++) {

        size_t bindx = find_element(arr + i, size - i, order);

        int tmp = arr[i];
        arr[i] = arr[bindx + i];
        arr[bindx + i] = tmp;
    }
    return 0;
}

int main(void) {
    int arr[] = {1, 50, 99, 36, 18, 23, 57, 69, 23, 43, 76};

    selectionsort(arr, sizeof(arr) / sizeof(arr[0]), DEFAULT_ORDER);

    printf("Default order:\t");
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d, ", arr[i]);
    }

    selectionsort(arr, sizeof(arr) / sizeof(arr[0]), REVERSE_ORDER);
    printf("\nReverse order:\t");
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d, ", arr[i]);
    }
    putchar('\n');
    return 0;
}
