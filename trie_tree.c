//
// Created by 吴裕欣 on 2018/12/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <wchar.h>
#include "trie_tree.h"

#define UTF8_CHAR_LEN( byte ) ((( 0xE5000000 >> (( byte >> 3 ) & 0x1e )) & 3 ) + 1)

void resize_children(trie_node **node_ref) {
    trie_node *new_node = NULL;

    if ((*node_ref) == NULL || (*node_ref)->children_count == 0) {
        new_node = calloc(1, sizeof(trie_node));
        new_node->key = calloc(4, sizeof(char));
        new_node->children_count = 2;
        new_node->children = calloc((size_t)new_node->children_count, sizeof(trie_node));
    } else {
        new_node = calloc(1, sizeof(trie_node));
        new_node->key = calloc(4, sizeof(char));
        new_node->children_count = 2 * (*node_ref)->children_count;
        new_node->children = calloc((size_t)new_node->children_count, sizeof(trie_node));
        memcpy(new_node->children, (*node_ref)->children, (*node_ref)->children_count * sizeof(*node_ref));
    }

    *node_ref = new_node;
}

void init(trie_tree **root, char *words, size_t len) {
    *root = calloc(1, sizeof(trie_tree));
    resize_children(&(*root)->root);
    trie_node *node_ref = (*root)->root;

    int utf8_len = 0;
    for (int i = 0; i < len; i++) {
        utf8_len = UTF8_CHAR_LEN(*(words + i));

        if (utf8_len > 0) {
            char wd[4] = {};
            memcpy(wd, (words + i), utf8_len);
            i += utf8_len - 1;

            if (strcmp(wd, ",") == 0) {
                node_ref = (*root)->root;
                continue;
            }

            bool found = false;
            for (int j = 0; j < (node_ref->next_index); ++j) {
                trie_node *n = *(node_ref->children + j);
                if (n != NULL && strcmp(n->key, wd) == 0) {
                    node_ref = n;
                    found = true;
                    break;
                }
            }

            if (!found) {
                trie_node *n = NULL;
                resize_children(&n);
                memcpy(n->key, wd, utf8_len);
                *(node_ref->children + node_ref->next_index) = n;
                node_ref->next_index++;
                node_ref = n;
            }
        }
    }
}

void print_node(trie_node *n) {
    if (n == NULL) return;

    for (int i = 0; i < n->next_index; ++i) {
        printf("%s", n->key);
        print_node(*(n->children + i));
    }
}

int main() {
    char *w = "王八羔子,王八蛋";
    const size_t len = strlen(w) + 1;

    trie_tree *root;
    init(&root, w, len);

    print_node(root->root);
}