//
// Created by william on 2018/12/6.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "priority_queues.h"

ElementType *pq;
ElementType *qp;
char **keys;
unsigned int N = 0;
char *strings[] = {"z", "c", "d", "a", "t", "q", "y", "h", "l", "q"};


void sink(int k) {
    while (k <= N / 2) {
        int i = 2 * k;
        if (i < N && strcmp(keys[pq[i + 1]], keys[pq[i]]) < 0) i++;
        if (strcmp(keys[pq[k]], keys[pq[i]]) < 0) break;
        swap(pq[k], pq[i]);
        k = i;
    }
}

void swim(unsigned int k) {
    while (k > 1 && strcmp(keys[pq[k]], keys[pq[k / 2]]) < 0) {
        swap(pq[k], pq[k / 2]);
        k /= 2;
    }
}

void insert(ElementType v, char *s) {
    pq[++N] = v;
    qp[v] = N;
    keys[v] = s;
    swim(N);
}

void exch(ElementType *a, ElementType *b) {
    if (*a != *b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
}

ElementType delMin() {
    ElementType v = pq[1];
    exch(&pq[1], &pq[N--]);
//    pq[N + 1] = -1; // 不需要 sink方法保证：不会访问N+1
    sink(1);
    return v;
}


int size() {
    return N;
}

//增序优先级队列
void IndexMinPQ() {
    unsigned int len = sizeof(strings) / sizeof(char *);
    pq = calloc(len + 1, sizeof(ElementType));
    qp = calloc(len + 1, sizeof(ElementType));
    keys = calloc(len + 1, sizeof(char *));
    char **arr = calloc(len, sizeof(ElementType));
    for (int i = 0; i < len; ++i) {
        insert(i, strings[i]);
    }
    for (int i = 1; i <= len / 2; ++i) {
        if (strcmp(keys[pq[2 * i]], keys[pq[i]]) < 0
            || (2 * i + 1 <= len && strcmp(keys[pq[2 * i + 1]], keys[pq[i]]) < 0)) {
            printf("pq is error, i = %d %s %s %s\n", i, keys[i], keys[2 * i], keys[2 * i + 1]);
            break;
        }
    }
    for (int i = 0; i < len; ++i) {
        arr[i] = keys[delMin()];
    }
    print_s(arr, len);
}

//模拟多路归并
void multiway() {
    char *s1[] = {"a", "b", "c", "d"};
    char *s2[] = {"a", "d", "d", "g"};
    char *s3[] = {"b", "d", "e", "z"};
    int lens[] = {0, 0, 0};
    char **s[] = {s1, s2, s3};
    unsigned int num_arr = 3;
    int arr_ele = 4;
    pq = calloc(num_arr + 1, sizeof(int));
    qp = calloc(num_arr + 1, sizeof(int));
    keys = calloc(num_arr + 1, sizeof(char *));
    for (int i = 0; i < num_arr; ++i) {
        insert(i, s[i][0]);
        lens[i]++;
    }

    while (size() > 0) {
        int min = delMin();
        printf("%s ", keys[min]);
        if (lens[min] < arr_ele)
            insert(min, s[min][lens[min]++]);
    }
    printf("\n");
}

int main() {
    multiway();
    IndexMinPQ();
}