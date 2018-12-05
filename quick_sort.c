//
// Created by 吴裕欣 on 2018/11/26.
//

#include "quick_sort.h"
#include "sort_check.h"

void q_sort(ElementType arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int l = low, r = high;
    ElementType tmp = arr[l]; // 假设 flag 位置

    while (l < r) {
        // 先从左边开始找一个大于 flag 的值
        while (l < r && arr[r] >= tmp) {
            r--;
        }

        // 再从右边找一个 小于 flag 的值
        while (l < r && arr[l] <= tmp) {
            l++;
        }

        // 如果找到的是满足条件的一组，则交换位置
        if (l < r) {
            ElementType t = arr[l];
            arr[l] = arr[r];
            arr[r] = t;
        }
        // 开始下一组查找
    }

    arr[low] = arr[r];
    arr[r] = tmp;

    q_sort(arr, low, r - 1);
    q_sort(arr, r + 1, high);
}

void q_sort2(ElementType arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int l = low, r = high;
    ElementType tmp = arr[l];

    while (l < r) {
        while (l < r && arr[r] >= tmp) {
            r--;
        }
        arr[l] = arr[r];
        while (l < r && arr[l] <= tmp) {
            l++;
        }
        arr[r] = arr[l];
    }

    arr[l] = tmp;

    q_sort2(arr, low, r - 1);
    q_sort2(arr, r + 1, high);
}

void quick_sort(ElementType arr[], int len) {
    q_sort2(arr, 0, len - 1);
}

int main() {
    ElementType a[] = {8, 7, 2, 9, 12, 3, 5, 6, 32, 1, 43, 2, 2};
    quick_sort(a, sizeof(a) / sizeof(int));

    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(int)));
    print_arr(a, sizeof(a) / sizeof(int));

}