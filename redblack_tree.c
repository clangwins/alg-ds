//
// Created by william on 2018/12/26.
//

#include "redblack_tree.h"
typedef struct Node {
  ElementType key;
  ElementType value;
  struct Node *left, *right;
  int N;
  bool color;

} *Node;

int size(Node n) {
    return n->N;
}

Node rotateLeft(Node h) {
    Node x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);

    return x;
}

Node rotateRight(Node h) {
    Node x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);

    return x;
}

void flipColors(Node h) {
    h->color = RED;
    h->right->color = h->left->color = BLACK;
}

int main() {
    Node n;
    return 0;
}