//NEED TO CHECK
#include "trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


TrieNode *trie_node_create(uint16_t index){
  TrieNode *node = (struct TrieNode *) malloc(1, sizeof(TrieNode));
  if(node != NULL){
    node->code = index;
  } else{
    node = NULL;
  }
  return node;

}

void trie_node_delete(TrieNode *n){
  if(node != NULL){
    free(node);
    node = NULL;
    return;
    }
}

TrieNode *trie_create(void){
  return trie_node_create(EMPTY_CODE);
}

void trie_reset(TrieNode *root){
  if(node != NULL){
    uint16_t i = 0;
    while(i < ALPHABET){
      if(root->children[i] != NULL){
        trie_delete(root->children[i]);
        root->children[i] = NULL;
      }
      i++;
    }
    return;
  }
}

void trie_delete(TrieNode *n){
  if(node != NULL){
      uint16_t i = 0;
      while(i < ALPHABET){
        trie_node_delete(node->children[i])
        i++;
      }
      trie_node_delete(node);
      node = NULL;
      return;
    }
}

TrieNode *trie_step(TrieNode *n, uint8_t sym){
  if(n->children[sym] == NULL){
    return NULL;
  }
   return n->children[sym];
}

