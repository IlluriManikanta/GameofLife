#//DONE
#include "mathlib.h"

#include <stdio.h>

static double count = 0.0;

double pi_viete(void) {
    double fraction = 0.0;
    double prev = 0.0;
    double tot = 1.0;

    for (; absolute(1.0 - fraction) >= EPSILON; count += 1.0) {
        prev = (sqrt_newton(2.0 + prev));
        fraction = prev / 2.0;
        tot *= fraction;
    }
    return (2.0 / tot);
}

int pi_viete_factors(void) {
    return (int) count;
}
