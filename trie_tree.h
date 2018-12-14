//
// Created by 吴裕欣 on 2018/12/13.
//

#ifndef ALG_DS_TRIE_TREE_H
#define ALG_DS_TRIE_TREE_H

#include <stdbool.h>

typedef struct trie_node_s {
    char *key;
    int children_count;
    int next_index;
    struct trie_node_s **children;
} trie_node;

typedef struct trie_tree_s {
    trie_node *root;
} trie_tree;

void init(trie_tree **root, char *words, size_t len);

#endif //ALG_DS_TRIE_TREE_H
