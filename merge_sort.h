//
// Created by william on 2018/11/27.
//

#ifndef CODE_MERGE_SORT_H
#define CODE_MERGE_SORT_H
#include "sort_check.h"
SORT_STATUS merge_sort(ElementType arr[], unsigned int len);
#define swap(a, b)({a ^= b; b ^= a; a ^= b;})
#endif //CODE_MERGE_SORT_H
