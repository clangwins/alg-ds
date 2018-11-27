//
// Created by william on 2018/11/27.
//

#ifndef CODE_SHELL_SORT_H
#define CODE_SHELL_SORT_H
#include <stdbool.h>
typedef int ElementType;
bool less(ElementType i, ElementType j);
void shell_sort(ElementType arr[], unsigned int len);

#endif //CODE_SHELL_SORT_H
