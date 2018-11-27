//
// Created by william on 2018/11/27.
// 希尔排序作为插入排序的引申版，以h-系列的方式(h = 3h+1)，将数据整合成部分有序，从而提高插入排序的速度，
//  排序之初，各个子数组都很短，排序之后子数组都是部分有序的，这两种情况都很适合插入排序

#include "sort_check.h"
#include "shell_sort.h"

//抽离比较函数--兼容其他类型数据结构
bool less(ElementType i, ElementType j) {
    if (i <= j) return true;
    return false;
}

void shell_sort(ElementType arr[], unsigned int len) {
    if (len == 0) return;
    int h = 1;
    int j;
    // 3x+1 递增序列:  1, 4, 13, 40, 121, 364, 1093, ...
    while (h < len / 3) h = 3 * h + 1;
    while (1 <= h) {
        for (int i = h; i < len; ++i) {
            ElementType t = arr[i];
            for (j = i; h <= j && less(t, arr[j - h]); j -= h) {
                arr[j] = arr[j - h];
            }
            arr[j] = t;
        }
        h /= 3;
    }
}

int main() {
    ElementType a[] = {8, 7, 9, 12, 3, 5, 6, 32, 1, 43, 2};
    shell_sort(a, sizeof(a) / sizeof(int));

    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
    return 0;
}