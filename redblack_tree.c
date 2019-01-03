//
// Created by william on 2018/12/26.
//

#include <stdlib.h>
#include "redblack_tree.h"

pNode initNode(ElementType key, ElementType val, COLOR color, int size) {
    pNode n = malloc(sizeof(Node));
    n->key = key;
    n->value = val;
    n->color = color;
    n->N = size;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void destroryNode(pNode n) {
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
        return initNode(key, val, RED, 0);
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

pNode min(pNode n) {
    if (n->left == NULL)
        return n;
    else
        return min(n->left);
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

pNode moveRedRight(pNode n) {
    flipColors(n);
    if (isRed(n->left->left)) {
        n = rotateRight(n);
        flipColors(n);
    }
    return n;
}

pNode deleteMinDo(pNode n) {
    if (n->left == NULL) {
        destroryNode(n);
        return NULL;
    }

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

pNode deleteMaxDo(pNode n) {

    if (isRed(n->left))
        n = rotateRight(n);

    if (n->right == NULL) {
        destroryNode(n);
        return NULL;
    }

    if (!isRed(n->right) && !isRed(n->right->left))
        n = moveRedRight(n);

    n->right = deleteMaxDo(n->right);

    return balance(n);

}

pNode deleteMax(pNode n) {
    if (!isRed(n->left) && !isRed(n->right))
        n->color = RED;

    n = deleteMaxDo(n);

    if (n != NULL) n->color = BLACK;
    return n;
}

pNode deleteDo(pNode n, ElementType key) {

    if (compare(key, n->key) < 0) {
        if (!isRed(n->left) && !isRed(n->left->left))
            n = moveRedLeft(n);

        n->left = deleteDo(n->left, key);
    } else {
        if (isRed(n->left))
            n = rotateRight(n);
        if (compare(key, n->key) == 0 && n->right == NULL)
            return NULL;
        if (!isRed(n->right) && !isRed(n->right->left))
            n = moveRedRight(n);

        if (compare(key, n->key) == 0) {
            pNode x = min(n->right);
            n->key = x->key;
            n->value = x->value;
            n->right = deleteMin(n->right);
        } else {
            n->right = deleteDo(n->right, key);
        }
    }
    return balance(n);

}

pNode delete(pNode n, ElementType key) {
    if (get(n, key) < 0) {
        return n;
    }
    if (!isRed(n->left) && !isRed(n->right))
        n->color = RED;

    n = deleteDo(n, key);

    if (n != NULL) n->color = BLACK;
    return n;
}

void output(ElementType Element) {
    printf("%d ", Element);
}

/* Print the tree, watch out for NullNode, */
/* and skip header */

static void printTree(pNode T) {
    if (T != NULL) {
        printTree(T->left);
        output(T->value);
        printTree(T->right);
    }
}

void destoryTree(pNode n) {
    if (n != NULL) {
        destoryTree(n->left);
        destoryTree(n->right);
        destroryNode(n);
    }
}

int main() {
    ElementType a[] = {1118, 7, 17, 43, 66, 9, 6, 1, 32, 3, 5, 6, 43, 2, 13, 23, 1, 44, 55, 22, 43, 66, 123, 456, 42};
    int len = sizeof(a) / sizeof(ElementType);
    pNode root = NULL;
    while (len-- > 0)
        root = put(root, a[len], a[len]);

    printf("bst number is: %d\n", root->N);
    printf("search not exist key 9999's value: %d\n", get(root, 9999));
    printTree(root);

    //test delete min
    root = deleteMin(root);
    root = deleteMin(root);
    printf("\n");
    printTree(root);

    //test delete max
    root = deleteMax(root);
    root = deleteMax(root);
    printf("\n");
    printTree(root);


    //test delete
    root = delete(root, 5);
    root = delete(root, 6);
    root = delete(root, 99999999);
    printf("\n");
    printTree(root);

    destoryTree(root);
}