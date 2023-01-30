//DONE
#include "mathlib.h"

#include <stdio.h>

static double count = 2.0;

double pi_euler(void) {
    double fnl = 1.0;
    double f = 1.0;
    double cs;

    for (; f > EPSILON; count += 1.0) {
        cs = count * count;
        f = 1.0 / cs;
        fnl += f;
    }

    return sqrt_newton(6 * fnl);
}

int pi_euler_terms(void) {
    return (int) count;
}
