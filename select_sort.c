//
// Created by 吴裕欣 on 2018/12/3.
//

#include "select_sort.h"
#include "sort_check.h"
#include "sort_tool.h"

int select_min_elem(ElementType arr[], int lo, int hi) {
    int k = lo;

    for (int i = lo+1; i < hi; ++i) {
        if (arr[i] < arr[k]) k = i;
    }

    return k;
}

/**
 * 单向选择排序，正常的选择排序，从数组中选择最小的数据，依次插入数组中
 * 此例中直接在原有的数组上进行修改，所以会涉及到数据交换的过程
 *
 * @param arr
 * @param len
 */
void select_sort(ElementType arr[], int len) {
    for (int i = 0; i < len; ++i) {
        int k = select_min_elem(arr, i, len);
        if (k != i) swap(arr[i], arr[k]);
    }
}

void select_elem(ElementType arr[], int lo, int hi, int *k, int *j) {
    *k = *j = lo;


    for (int i = lo+1; i < hi; ++i) {
        if (arr[i] < arr[*k]) *k = i;
        if (arr[*j] < arr[i]) *j = i;
    }
}

/**
 * 双向选择排序，在单向基础，由两边往中间排序过程
 *
 * @param arr
 * @param len
 */
void select_sort2(ElementType arr[], int len) {
    for (int i = 0, j = len - 1; i < j; ++i, --j) {
        int max, min;
        select_elem(arr, i, len - i, &min, &max);

        swap(arr[i], arr[min]);
        if (max == i) max = min;
        swap(arr[max], arr[j]);
    }
}

int main() {
    ElementType a[] = {1118, 7, 17, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 8, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    select_sort2(a, sizeof(a) / sizeof(a[0]));

    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(a[0])));
    print_arr(a, sizeof(a) / sizeof(a[0]));
}