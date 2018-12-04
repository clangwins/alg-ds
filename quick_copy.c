//
// Created by william on 2018/12/3.
//

#include <assert.h>
#include "quick_copy.h"

int partition(ElementType arr[], int lo, int hi) {
    ElementType v = arr[lo];
    int i = lo, j = hi + 1;

    while (true) {
        while (less(arr[++i], v));
        while (less(v, arr[--j]));
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }

    swap(arr[lo], arr[j]);
    return j;
}

void sort(ElementType arr[], int lo, int hi) {
    if (hi <= lo) return;

    int j = partition(arr, lo, hi);
    sort(arr, lo, j - 1);
    sort(arr, j + 1, hi);
}

void quick_sort(ElementType arr[], int len) {
    sort(arr, 0, len - 1);
    assert(check_sorted(arr, len));
}

int main() {
    ElementType a[] = {8, 7, 17, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 8, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    quick_sort(a, sizeof(a) / sizeof(ElementType));
    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
}
