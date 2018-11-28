//
// Created by william on 2018/11/27.
//

#include <stdlib.h>
#include "merge_sort.h"
#include "sort_tool.h"
const int CUTOFF = 7;
void merge(ElementType arr[], ElementType arrTmp[], unsigned int lo, unsigned int mid, unsigned int hi) {
    unsigned int i = lo, j = mid + 1, n = hi - lo + 1;
    for (int k = lo; k <= hi; ++k) {
        if (i > mid) arrTmp[k] = arr[j++];
        else if (j > hi) arrTmp[k] = arr[i++];
        else if (less(arr[i], arr[j])) arrTmp[k] = arr[i++];
        else arrTmp[k] = arr[j++];
    }
    for (int i = 0; i < n; i++, hi--)
        arr[hi] = arrTmp[hi];
}

void insert_sort(ElementType arr[], unsigned int lo, unsigned int hi) {
    if (hi <= lo) return;
    for (int i = lo; i <= hi; i++)
        for (int j = i; j > lo && less(arr[j], arr[j - 1]); j--)
            swap(arr[j], arr[j - 1]);
}

void sort(ElementType arr[], ElementType arrTmp[], unsigned int lo, unsigned int hi) {
    //优化点1: 切换小数组至insert_sort
    if (hi <= lo + CUTOFF) {
        insert_sort(arr, lo, hi);
        return;
    }

    unsigned int mid = lo + (hi - lo) / 2;
    sort(arr, arrTmp, lo, mid);
    sort(arr, arrTmp, mid + 1, hi);
    //优化点2: 已经有序则跳过合并
    if (arr[mid + 1] < arr[mid]) merge(arr, arrTmp, lo, mid, hi);
}
SORT_STATUS merge_sort(ElementType arr[], unsigned int len) {
    ElementType *arrTmp = calloc(sizeof(ElementType), len);

    if (arrTmp != NULL) {
        sort(arr, arrTmp, 0, len - 1);
        free(arrTmp);
        return SORT_FIN;
    }
    return SORT_FAIL;
}

int main() {
    ElementType a[] = {8, 7, 17, 9, 1, 32, 3, 5, 6, 43, 2, 13, 23, 44, 55, 22, 43, 66, 123, 456, 42};
    merge_sort(a, sizeof(a) / sizeof(int));

    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
}
