//
// Created by william on 2018/12/3.
//

#include <assert.h>
#include "quick_copy.h"
//小数组切换到插入排序 -- 针对7~15均可
const int CUTOFF = 7;

int median3(ElementType arr[], int i, int j, int k) {
    return (less(arr[i], arr[j]) ?
            (less(arr[j], arr[k]) ? j : less(arr[i], arr[k]) ? k : i) :
            (less(arr[k], arr[j]) ? j : less(arr[k], arr[i]) ? k : i));
}

int partition(ElementType arr[], int lo, int hi) {
    //优化逻辑, 选择三点中位数作为切分点
    int m = median3(arr, lo, lo + (hi - lo + 1) / 2, hi);
    swap(arr[m], arr[lo]);

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
void sort_repeat(ElementType arr[], int lo, int hi) {
    //优化逻辑, 小数组用插入排序优化
    if (hi <= lo + CUTOFF) {
        insert_sort(arr, lo, hi);
        return;
    };

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

void quick_sort(ElementType arr[], unsigned int len) {
    //todo: 此处省略数据随机化的操作, 根据实际情况处理, 因为快排是偏随机的算法
    sort_repeat(arr, 0, len - 1);
    assert(check_sorted(arr, len));
    sort(arr, 0, len - 1);
    assert(check_sorted(arr, len));
}

int main() {
    ElementType a[] = {8, 7, 17, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 8, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    quick_sort(a, sizeof(a) / sizeof(ElementType));
    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
}
