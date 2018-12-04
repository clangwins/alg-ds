//
// Created by william on 2018/12/4.
//

#include "select.h"
#include "sort_check.h"
#include "sort_tool.h"

int compare(ElementType i, ElementType j) {
    return i - j;
}
void extremum(ElementType arr[], int lo, int hi, int *max, int *min) {
    *max = *min = lo;
    while (lo <= hi) {
        if (compare(arr[hi], arr[*min]) <= 0) *min = hi;
        if (compare(arr[*max], arr[hi]) <= 0) *max = hi;
        hi--;
    }
}
void select_sort(ElementType arr[], unsigned int len) {
    int j = len;
    int max = 0, min = 0;
    bool iseven = len % 2 == 0 ? true : false;

    while (len / 2 < j--) {
        int i = len - j - 1;
        extremum(arr, i, j, &max, &min);
        swap(arr[i], arr[min]);

        //处理偶数行为
        if (iseven && j <= i) break;

        if (max == i) continue;

        swap(arr[j], arr[max]);
    }

}
int main() {
    ElementType a[] = {8, 7, 17, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 8, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    select_sort(a, sizeof(a) / sizeof(ElementType));
    printf("%d\n", check_sorted(a, sizeof(a) / sizeof(ElementType)));
    print_arr(a, sizeof(a) / sizeof(int));
}