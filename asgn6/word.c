//DONE
#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *word = (Word *) malloc(sizeof(Word));
    if (word != NULL) {
        word->syms = (uint8_t *) malloc(sizeof(uint8_t));
        word->len = len;
        if (word->syms) {
            uint32_t i = 0;
            while (i < len) {
                word->syms[i] = syms[i];
                i++;
            }
        }
    }
    return word;
}

Word *word_append_sym(Word *w, uint8_t sym) {
    Word *new_append = (Word *) calloc(1, sizeof(Word));
    new_append->len = w->len + 1;
    new_append->syms = (uint8_t *) malloc(new_append->len * sizeof(uint8_t));

    if (w->len) {
        memcpy(new_append->syms, w->syms,
            w->len); //memcpy was used to copy a memory block from one location to another.
    }

    new_append->syms[w->len] = sym;
    return new_append;
}

void word_delete(Word *w) {
    if (w->syms) {
        free(w->syms);
        w->syms = NULL;
    }
    free(w);
    w = NULL;
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(Word));
    if (wt != NULL) {
        uint16_t i = 0;
        while (i < MAX_CODE) {
            wt[i] = NULL;
            i++;
        }
        wt[EMPTY_CODE] = word_create(NULL, 0);
        if (wt[EMPTY_CODE] == NULL) {
            uint16_t i = 0;
            while (i < MAX_CODE) {
                word_delete(wt[i]);
                i++;
            }
            free(wt);
            return NULL;
        }
    }
    return wt;
}

void wt_reset(WordTable *wt) {
    if (wt != NULL) {
        uint32_t i = START_CODE;
        while (i < MAX_CODE) {
            if (wt[i] != NULL) {
                word_delete(wt[i]);
                wt[i] = NULL;
            }
            i++;
        }
    }
}

void wt_delete(WordTable *wt) {
    if (wt != NULL) {
        uint32_t i = 0;
        while (i < MAX_CODE) {
            if (wt[i]) {
                word_delete(wt[i]);
                wt[i] = NULL;
            }
            i++;
        }
        free(wt);
        return;
    }
}
