//
// Created by 吴裕欣 on 2018/11/27.
//

#include "bubble_sort.h"
#include "sort_check.h"

int compare_times = 0;
int step_times = 0;

bool compare(ElementType a, ElementType b) {
    compare_times++;

    return a < b;
}

void swap(ElementType *a, ElementType *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

/**
 * 冒泡排序是学习排序时最基本的排序之一
 * 我个人认为，快速排序与它关系很大，因为快速排序可以认为是一个双向的冒泡
 * 最基本的冒泡排序是会走完所有的比较
 */
void bubble_sort(ElementType arr[], int len) {
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (compare(arr[j + 1], arr[j])) {
                swap(&arr[j + 1], &arr[j]);
            }
        }
        step_times++;
    }
}

/**
 * 在上面的基础，下面加入 flag ，尽可能减少交换次数
 */
void bubble_sort2(ElementType arr[], int len) {
    bool flag = true;
    for (int i = 0; i < len - 1 && flag; ++i) {
        flag = false;
        for (int j = 0; j < len - i - 1; ++j) {
            if (compare(arr[j + 1], arr[j])) {
                swap(&arr[j + 1], &arr[j]);
                flag = true;
            }
        }
        step_times++;
    }
}

int main() {
    ElementType a[] = {12, 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    step_times = 0;
    compare_times = 0;
    bubble_sort(a, sizeof(a) / sizeof(a[0]));
    printf("step times: %d  compare times: %d\n", step_times, compare_times);
    print_arr(a, sizeof(a) / sizeof(a[0]));
    printf("\n");

    ElementType b[] = {12, 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    step_times = 0;
    compare_times = 0;
    bubble_sort2(b, sizeof(b) / sizeof(b[0]));
    printf("step times with flag: %d  compare times: %d\n", step_times, compare_times);
    print_arr(b, sizeof(b) / sizeof(b[0]));

    return 0;
}