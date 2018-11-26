//
// Created by william on 2018/11/26.
//
#include "insert_sort.h"
#include "sort_check.h"

void insert_sort(ElementType arr[], unsigned int len) {
    if (len == 0) return;

    for (int i = 1; i < len; ++i) {
        ElementType v = arr[i];
        int j = i - 1;
        while (v < arr[j]) {
            arr[j + 1] = arr[j];
            if (j-- == 0) break;
        }
        arr[j + 1] = v;
    }

}

int main() {
    ElementType a[] = {8,7, 9, 12, 3, 5, 6, 32, 1, 43, 2};
    insert_sort(a, sizeof(a) / sizeof(int));

    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(int)));
    print_arr(a, sizeof(a) / sizeof(int));

}
