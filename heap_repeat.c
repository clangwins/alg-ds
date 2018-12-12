//
// Created by william on 2018/12/10.
//

#include <assert.h>
#include "heap_repeat.h"
void sink(ElementType arr[], int k, int N) {
    while (k < N / 2) {
        int i = 2 * k + 1;
        if (i < N && less(arr[i], arr[i + 1])) i++;
        if (less(arr[i], arr[k])) break;
        swap(arr[k], arr[i]);
        k = i;
    }
}

void heap_sort(ElementType arr[], unsigned int len) {
    for (int j = len / 2; j >= 0; --j) {
        sink(arr, j, len);
    }

    while (--len > 0) {
        swap(arr[0], arr[len]);  /* DeleteMax */
        sink(arr, 0, len - 1);
    }

}

int main() {
    ElementType a[] = {1118, 7, 17, 43, 66, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    heap_sort(a, sizeof(a) / sizeof(ElementType));
    assert(check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
}
