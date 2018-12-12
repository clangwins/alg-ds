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

/*
 * 从前向后排序，比如：针对list结构， 则可以实现就地排序，无需额外空间。
 */
SORT_STATUS merge_sort_u(ElementType arr[], unsigned int len) {
    ElementType *arrTmp = calloc(len, sizeof(ElementType));
    if (arrTmp != NULL) {
        for (unsigned int sz = 1; sz < len; sz *= 2) {
            printf("sz = %d\n", sz);
            for (unsigned int lo = 0; lo < len - sz; lo += 2 * sz) {
                unsigned int mid = lo + sz - 1;
                unsigned int hi = ((mid + sz) < (len - 1)) ? (mid + sz) : (len - 1);
                merge(arr, arrTmp, lo, mid, hi);
            }
        }
        free(arrTmp);
        return SORT_FIN;
    }
    return SORT_FAIL;

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
    merge_sort_u(a, sizeof(a) / sizeof(int));
    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));

    ElementType b[] = {8, 7, 17, 9, 1, 32, 3, 5, 6, 43, 2, 13, 23, 44, 55, 22, 43, 66, 123, 456, 42};
    merge_sort(b, sizeof(b) / sizeof(ElementType));
    printf("%d\n", check_sorted(b, sizeof(b) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(ElementType));
}
