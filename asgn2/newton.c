//DONE
#include <stdio.h>
#include "mathlib.h"

static double count = 0.0;

double sqrt_newton(double x){
	double tmp = 0.0;
	double ele = 1.0;

	for(;absolute(ele - tmp) > EPSILON; count += 1.0){
		tmp = ele;
		ele = 0.5 * (tmp + (x / tmp));
		count += 1.0;	
	}
	return ele;
}

int sqrt_newton_iters(void){
	return (int)count;
}

