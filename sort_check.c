//
// Created by william on 2018/11/26.
//

#include "sort_check.h"

bool check_sorted(ElementType arr[], unsigned int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i + 1] < arr[i]) {
            return false;
        }

    }

    return true;
}

void print_arr(ElementType arr[], unsigned int len) {
    int i = 0;
    while (++i < len) {
        printf("%d ", arr[i]);
    }
}