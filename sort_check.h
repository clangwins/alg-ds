//
// Created by william on 2018/11/26.
//
#ifndef CODE_SORT_CHECK_H
#define CODE_SORT_CHECK_H

#include <stdbool.h>
#include <stdio.h>
typedef int ElementType;
bool check_sorted(ElementType arr[], unsigned int len);
void print_arr(ElementType arr[], unsigned int len);
typedef enum { SORT_FAIL = -1, SORT_FIN } SORT_STATUS;
#endif //CODE_SORT_CHECK_H
