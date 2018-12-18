//
// Created by 吴裕欣 on 2018/12/13.
//

#ifndef ALG_DS_TRIE_TREE_H
#define ALG_DS_TRIE_TREE_H

#include <stdbool.h>

#define MIN_CHILDREN 4

typedef struct trie_node_s {
    char *key;
    int count;
    int index;
    struct trie_node_s* children[MIN_CHILDREN];
} trie_node;

typedef struct trie_tree_s {
    trie_node *root;
} trie_tree;

trie_tree* create();

#endif //ALG_DS_TRIE_TREE_H
