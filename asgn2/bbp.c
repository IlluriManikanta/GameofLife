//DONE (value a little off)
#include "mathlib.h"

#include <stdio.h>

static double count = 0.0;


double pi_bbp(void) {
    double fnl = 1.0;
    double tot = 0.0;
    double one;
    double two;
    double three;
    double four;


    for (; absolute(fnl) > EPSILON; count += 1.0) {

        one = 4.0 / ((8.0 * count) + 1.0);
        two = 2.0 / ((8.0 * count) + 4.0);
        three = 1.0 / ((8.0 * count) + 5.0);
        four = 1.0 / ((8.0 * count) + 6.0);
        fnl = (one - two - three - four);
        for(int i = 0; i < count; i++){
        	fnl = fnl / 16;	
        }
        tot += fnl;
    }
    return tot;
}

int pi_bbp_terms(void) {
    return (int) count;
}
