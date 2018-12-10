//
// Created by william on 2018/12/6.
//

#include <stdlib.h>
#include <assert.h>
#include "priority_queues.h"

ElementType *pq;
unsigned int N = 0;

void sink(int k) {
    while (k <= N / 2) {
        int i = 2 * k;
        int l = less(pq[i], pq[i + 1]) ? i + 1 : i;
        if (!less(pq[k], pq[l])) break;
        swap(pq[k], pq[l]);
        k = l;
    }
}

void swim(unsigned int k) {
    while (k > 1 && less(pq[k / 2], pq[k])) {
        swap(pq[k], pq[k / 2]);
        k /= 2;
    }
}
void insert(ElementType v) {
    pq[++N] = v;
    swim(N);
}
void exch(ElementType *a, ElementType *b) {
    if (*a != *b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}
ElementType delMax() {
    ElementType v = pq[1];
    exch(&pq[1], &pq[N--]);
    pq[N + 1] = 0;
    sink(1);
    return v;
}

void IndexMaxPQ(ElementType arr[], unsigned int len) {

    pq = calloc(sizeof(NULL), len);
    for (int i = 0; i < len; ++i) {
        insert(arr[i]);
    }
    for (int i = 1; i <= len / 2; ++i) {
        if (less(pq[i], pq[2 * i]) || (2 * i + 1 <= len && less(pq[i], pq[2 * i + 1]))) {
            printf("pq is error, i = %d\n", i);
            break;
        }
    }
    for (int i = 0; i < len; ++i) {
        arr[len - i - 1] = delMax();
    }
    assert(check_sorted(arr, len));
}

int main() {
    ElementType a[] = {1118, 7, 17, 43, 66, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 1, 44, 55, 22, 43, 66, 123, 456, 42};

    IndexMaxPQ(a, sizeof(a) / sizeof(ElementType));
    print_arr(a, sizeof(a) / sizeof(int));
}