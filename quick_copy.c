//
// Created by william on 2018/12/3.
//

#include <assert.h>
#include "quick_copy.h"
//小数组切换到插入排序 -- 针对7~15均可
const int CUTOFF = 7;
const int MEDIAN_OF_3_CUTOFF = 40;
int median3(ElementType arr[], int i, int j, int k) {
    return (less(arr[i], arr[j]) ?
            (less(arr[j], arr[k]) ? j : less(arr[i], arr[k]) ? k : i) :
            (less(arr[k], arr[j]) ? j : less(arr[k], arr[i]) ? k : i));
}

void median_of_3(ElementType arr[], int lo, int hi) {
    //优化逻辑, 选择三点中位数作为切分点
    int n = hi - lo + 1;
    if (n < MEDIAN_OF_3_CUTOFF) {
        int m = median3(arr, lo, lo + n / 2, hi);
        swap(arr[m], arr[lo]);
    } else {
        int eps = n / 8;
        int mid = lo + n / 2;
        int m1 = median3(arr, lo, lo + eps, lo + eps + eps);
        int m2 = median3(arr, mid - eps, mid, mid + eps);
        int m3 = median3(arr, hi - eps - eps, hi - eps, hi);
        int ninther = median3(arr, m1, m2, m3);
        swap(arr[ninther], arr[lo]);
    }
}

int partition(ElementType arr[], int lo, int hi) {
    median_of_3(arr, lo, hi);
    int i = lo, j = hi + 1;
    ElementType v = arr[lo];
    while (true) {
        while (less(arr[++i], v));
        while (less(v, arr[--j]));
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }

    swap(arr[lo], arr[j]);
    return j;
}

void insert_sort(ElementType arr[], int lo, int hi) {
    if (hi <= lo) return;
    for (int i = lo; i <= hi; i++)
        for (int j = i; j > lo && less(arr[j], arr[j - 1]); j--)
            swap(arr[j], arr[j - 1]);
}

void sort(ElementType arr[], int lo, int hi) {
    //优化逻辑, 小数组用插入排序优化
    if (hi <= lo + CUTOFF) {
        insert_sort(arr, lo, hi);
        return;
    };

    int j = partition(arr, lo, hi);
    sort(arr, lo, j - 1);
    sort(arr, j + 1, hi);
}

void exch(ElementType *a, ElementType *b) {
    if (*a != *b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

//应对大量重复元素的序列，排序效果较好
void sort_repeat(ElementType arr[], int lo, int hi) {
    //优化逻辑, 小数组用插入排序优化
    if (hi <= lo + CUTOFF) {
        insert_sort(arr, lo, hi);
        return;
    };

    median_of_3(arr, lo, hi);

    int lt = lo, i = lo + 1, gt = hi;
    ElementType v = arr[lo];

    while (i <= gt) {
        int comp = compare(arr[i], v);
        if (comp < 0) exch(&arr[i++], &arr[lt++]);
        else if (comp > 0)exch(&arr[i], &arr[gt--]);
        else i++;
    }

    sort_repeat(arr, lo, lt - 1);
    sort_repeat(arr, gt + 1, hi);

}

//解决sort_repeat针对重复元素不多的优化，交换次数较少，
void sort_repeat_less(ElementType arr[], int lo, int hi) {
    //优化逻辑, 小数组用插入排序优化
    if (hi <= lo + CUTOFF) {
        insert_sort(arr, lo, hi);
        return;
    };

    median_of_3(arr, lo, hi);

    int i = lo, j = hi + 1, p = i, q = j;
    ElementType v = arr[lo];
    while (true) {
        while (less(arr[++i], v) && i <= hi);
        while (less(v, arr[--j]) && j >= lo);
        if (i == j && (arr[i] == v)) exch(&arr[++p], &arr[i]);

        if (i >= j) break;

        swap(arr[i], arr[j]);

        if (arr[i] == v) exch(&arr[++p], &arr[i]);
        if (arr[j] == v) exch(&arr[--q], &arr[j]);
    }

    i = j + 1;
    for (int k = lo; k <= p; ++k) exch(&arr[k], &arr[j--]);

    for (int k = hi; k >= q; --k) exch(&arr[k], &arr[i++]);

    sort_repeat_less(arr, lo, j);
    sort_repeat_less(arr, i, hi);
}

void quick_sort(ElementType arr[], unsigned int len) {
    //todo: 此处省略数据随机化的操作, 根据实际情况处理, 因为快排是偏随机的算法
    sort_repeat_less(arr, 0, len - 1);
    assert(check_sorted(arr, len));
    sort_repeat(arr, 0, len - 1);
    assert(check_sorted(arr, len));
    sort(arr, 0, len - 1);
    assert(check_sorted(arr, len));
}

int main() {
    ElementType a[] = {1118, 7, 17, 43, 66, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    quick_sort(a, sizeof(a) / sizeof(ElementType));
    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
}
