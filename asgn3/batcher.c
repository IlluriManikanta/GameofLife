//DONE
#include "stats.h"

#include <stdint.h>
#include <stdio.h>

uint32_t bitlength(uint32_t x) {
    uint32_t val = 0;
    while (x) {
        val++;
        x >>= 1;
    }
    return val;
}

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) == 1) {
        swap(stats, &A[x], &A[y]);
    }
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    //uint32_t n_len = n;
    uint32_t t = bitlength(n);
    uint32_t p = 1 << (t - 1);

    while (cmp(stats, p, 0) == 1) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < n - d; i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
