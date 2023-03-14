//DONE
#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint32_t len) {
    Word *word = (Word *) malloc(sizeof(Word));
    if (word != NULL) {
        word->syms = (uint8_t *) calloc(len, sizeof(uint8_t));
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

//Got it from TA help section Varun. He helped me debugging and fixing this part of my program.
Word *word_append_sym(Word *w, uint8_t sym) {
    Word *new_append = (Word *) malloc(sizeof(Word));
    new_append->len = w->len + 1;
    new_append->syms = (uint8_t *) malloc((new_append->len + 1) * sizeof(uint8_t));

    if (w->len) {
        uint32_t i = 0;
        while (i < w->len) {
            new_append->syms[i] = w->syms[i];
            i++;
        }

        new_append->syms[w->len] = sym;
        new_append->len = w->len + 1;
        return new_append;

    } else {
        return word_create(&sym, EMPTY_CODE);
    }
}

void word_delete(Word *w) {
    if (w) {
        if (w->syms) {
            free(w->syms);
            w->syms = NULL;
        }
        free(w);
        w = NULL;
    }
}

WordTable *wt_create(void) {
    WordTable *wt = (WordTable *) calloc(MAX_CODE, sizeof(WordTable));
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
