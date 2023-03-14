//DONE
#include "trie.h"
#include "code.h"
#include "endian.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

TrieNode *trie_node_create(uint16_t index) {
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));
    if (node) {
        node->code = index;
        int i = 0;
        while (i < ALPHABET) {
            node->children[i] = NULL;
            i++;
        }
    } else {
        node = NULL;
    }
    return node;
}

void trie_node_delete(TrieNode *n) {
    if (n != NULL) {
        free(n);
        n = NULL;
        return;
    }
}

TrieNode *trie_create(void) {
    return trie_node_create(EMPTY_CODE);
}

void trie_reset(TrieNode *root) {
    if (root) {
        uint16_t i = 0;
        while (i < ALPHABET) {
            if (root->children[i] != NULL) {
                trie_delete(root->children[i]);
                root->children[i] = NULL;
            }
            i++;
        }
        return;
    }
}

void trie_delete(TrieNode *n) {

    uint16_t i = 0;
    while (i < ALPHABET) {
        trie_node_delete(n->children[i]);
        i++;
    }
    free(n);
    n = NULL;
    return;
}

TrieNode *trie_step(TrieNode *n, uint8_t sym) {
    if (n->children[sym] == NULL) {
        return NULL;
    }
    return n->children[sym];
}
