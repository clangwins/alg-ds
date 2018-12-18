//
// Created by 吴裕欣 on 2018/12/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <wchar.h>
#include <iconv.h>
#include <locale.h>
#include "trie_tree.h"

#define UTF8_CHAR_LEN( byte ) ((( 0xE5000000 >> (( byte >> 3 ) & 0x1e )) & 3 ) + 1)

void init_node(trie_node *n, char *k) {
    n->key = calloc(4, sizeof(char));
    memcpy(n->key, k, strlen(k));
    n->count = MIN_CHILDREN;
}

trie_tree* create() {
    trie_tree *t = calloc(1, sizeof(trie_tree));
    trie_node *n = calloc(1, sizeof(trie_node));
    init_node(n, "\0");
    t->root = n;

    return t;
}

int compare(trie_node *n, char *k) {
    if (n == NULL) return -1;

    return strcmp(n->key, k);
}

trie_node* get_next(trie_node *n, char *word) {
    for (int i = 0; i < n->index; ++i) {
        trie_node *p = n->children[i];
        if (compare(p, word) == 0) {
            return p;
        }
    }

    return NULL;
}

void update(trie_node *n, char *word) {
    size_t len = strlen(word);
    int utf8_len = 0;

    for (int i = 0; i < len; ++i) {
        utf8_len = UTF8_CHAR_LEN(*(word + i));
        if (utf8_len > 0) {
            char wd[4] = {};
            memcpy(wd, (word + i), utf8_len);
            i += utf8_len - 1;

            trie_node *p = get_next(n, wd);

            if (p != NULL) {
                n = p;
            } else {
                p = calloc(1, sizeof(trie_node));
                init_node(p, wd);
                n->children[n->index++] = p;
                n = p;
            }
        }
    }
}

void insert(trie_tree *t, char *words[], int len) {
    trie_node *n = t->root;

    for (int i = 0; i < len; ++i) {
        char *word = *(words + i);
        update(n, word);
    }
}

void print_node(trie_node *n) {
    if (n == NULL) return;
    printf("%s\n", n->key);

    for (int i = 0; i < n->index; ++i) {
        print_node(n->children[i]);
    }
}

//int search(trie_tree *t, char *word) {
//    trie_node *n = t->root;
//    size_t len = strlen(word);
//    int utf8_len = 0;
//    int wd_len = 0;
//    bool flag = false;
//
//    for (int i = 0; i < len; ++i) {
//        utf8_len = UTF8_CHAR_LEN(*(word + i));
//        if (utf8_len > 0) {
//            char wd[4] = {};
//            memcpy(wd, (word + i), utf8_len);
//            trie_node *p = get_next(n, wd);
//            if (p == NULL) {
//                break;
//            }
//
//            wd_len++;
//            if (p->index > 0) {
//                n = p;
//            } else {
//                flag = true;
//            }
//        }
//    }
//
//    if (flag)  {
//        wd_len = 0;
//    }
//
//    return wd_len;
//}

int main() {
    char *w[2] = {"王八羔子", "王八蛋"};
    trie_tree *t = create();
    insert(t, w, 2);

    print_node(t->root);

//    char *ctx = "你就是个王八蛋";
//    int pos = search(t, ctx);
//
//    printf("%d\n", pos);
}