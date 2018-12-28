//
// Created by william on 2018/12/26.
//

#ifndef ALG_DS_REDBLACK_TREE_H
#define ALG_DS_REDBLACK_TREE_H

#include "sort_tool.h"

#define isRed(n)({ n != NULL && n->color == RED;})
#define flipColors(h) ({h->color = RED;h->right->color = h->left->color = BLACK; })

typedef enum COLOR { RED = 0, BLACK } COLOR;
typedef struct Node {
  ElementType key;
  ElementType value;
  struct Node *left, *right;
  int N;
  bool color;

} *pNode, Node;
pNode InitNode(ElementType key, ElementType val, COLOR color, int size);

#endif //ALG_DS_REDBLACK_TREE_H

