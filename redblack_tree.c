//
// Created by william on 2018/12/26.
//

#include <stdlib.h>
#include "redblack_tree.h"

pNode InitNode(ElementType key, ElementType val, COLOR color, int size) {
    pNode n = malloc(sizeof(Node));
    n->key = key;
    n->value = val;
    n->color = color;
    n->N = size;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void DestroryNode(pNode n) {
    free(n);
}

int size(pNode n) {
    if (n == NULL) return 0;
    return n->N;
}

pNode rotateLeft(pNode h) {
    pNode x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);

    return x;
}

pNode rotateRight(pNode h) {
    pNode x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    x->N = h->N;
    h->N = 1 + size(h->left) + size(h->right);

    return x;
}

pNode putHandler(pNode n, ElementType key, ElementType val) {
    if (n == NULL) {
        return InitNode(key, val, RED, 0);
    }
    int cmp = compare(key, n->key);

    if (cmp < 0) n->left = putHandler(n->left, key, val);
    else if (cmp > 0) n->right = putHandler(n->right, key, val);
    else n->value = val;

    if (isRed(n->right) && !isRed(n->left)) n = rotateLeft(n);
    if (isRed(n->left) && isRed(n->left->left)) n = rotateRight(n);
    if (isRed(n->right) && isRed(n->left)) flipColors(n);

    n->N = size(n->left) + size(n->right) + 1;

    return n;
}
pNode put(pNode root, ElementType key, ElementType val) {
    root = putHandler(root, key, val);
    root->color = BLACK;
    return root;
}

ElementType get(pNode n, ElementType key) {
    while (n != NULL) {
        int cmp = compare(key, n->key);
        if (cmp > 0) n = n->right;
        else if (cmp < 0) n = n->left;
        else return n->value;
    }
    return -1;
}

//TODO delete: delete key in node and return key's value
ElementType delete(pNode n, ElementType key) {
    return -1;
}

pNode balance(pNode n) {
    if (isRed(n->right)) n = rotateLeft(n);
    if (isRed(n->left) && isRed(n->left->left)) n = rotateRight(n);
    if (isRed(n->left) && isRed(n->right)) flipColors(n);
    n->N = size(n->left) + size(n->right) + 1;
    return n;
}

pNode moveRedLeft(pNode n) {
    flipColors(n);
    if (isRed(n->right->left)) {
        n->right = rotateRight(n->right);
        n = rotateLeft(n);
        flipColors(n);
    }
    return n;
}

pNode deleteMinDo(pNode n) {
    if (n->left == NULL)
        return NULL;

    if (!isRed(n->left) && !isRed(n->left->left))
        n = moveRedLeft(n);

    n->left = deleteMinDo(n->left);

    return balance(n);

}
pNode deleteMin(pNode n) {
    if (!isRed(n->left) && !isRed(n->right))
        n->color = RED;

    n = deleteMinDo(n);

    if (n != NULL) n->color = BLACK;
    return n;
}

//TODO delete max: delete max key in node and return key's value
ElementType deleteMax(pNode n, ElementType key) {
    return -1;
}

void Output(ElementType Element) {
    printf("%d ", Element);
}

/* Print the tree, watch out for NullNode, */
/* and skip header */

static void DoPrint(pNode T) {
    if (T != NULL) {
        DoPrint(T->left);
        Output(T->value);
        DoPrint(T->right);
    }
}

void PrintTree(pNode T) {
    DoPrint(T);
}

int main() {
    ElementType a[] = {1118, 7, 17, 43, 66, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    int len = sizeof(a) / sizeof(ElementType);
    pNode root = NULL;
    while (len-- > 0)
        root = put(root, a[len], a[len]);

    printf("bst number is: %d\n", root->N);
    printf("search not exist key 9999's value: %d\n", get(root, 9999));
    PrintTree(root);

    //test delete min
    root = deleteMin(root);
    root = deleteMin(root);
    printf("\n");
    PrintTree(root);

}