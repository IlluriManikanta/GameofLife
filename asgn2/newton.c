//DONE
#include "mathlib.h"

#include <stdio.h>

static int count = 0;

double sqrt_newton(double x) {
    double tmp = 0.0;
    double ele = 1.0;

    while (absolute(ele - tmp) > EPSILON) {
        tmp = ele;
        ele = 0.5 * (tmp + (x / tmp));
        count++;
    }
    return ele;
}

int sqrt_newton_iters(void) {
    //resetting counter
    int var = count;
    count = 0;

    return (int) var;
}
