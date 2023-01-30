//DONE
#include "mathlib.h"

#include <stdio.h>

//Counter stats from 1 becasue k value cannot start from 0 beacsue it would still equal 1, this is to avoid an extariteration.

static double count = 1.0;

double pi_madhava(void) {
    double fnl = 1.0;
    double num = 1.0;
    double den;
    double tmp = 1.0;

    for (; absolute(tmp) > EPSILON; count += 1.0) {
        num *= -1.0 / 3.0;
        den = (2.0 * count) + 1.0;
        tmp = num / den;
        fnl += tmp;
    }
    return (sqrt_newton(12.0) * fnl);
}

int pi_madhava_terms(void) {
    return (int) count;
}
