//DONE (value a little off)
#include <stdio.h>
#include "mathlib.h"

static double count = 0.0;

double pow(double b, double expo){
	double fnl = b;
	for (double i = 0.0; i <= expo; i+= 1.0) {
		if (b != 0 && expo == 0){
			return 1.0;
		} 
		fnl = fnl * b;
	}
	return (1.0 / fnl);
}


double pi_bbp(void){
	double fnl = 1.0;
	double tot = 0.0;
	double one;
	double two; 
	double three;
	double four;
	double tmp;
	
	for(;absolute(fnl) > EPSILON; count += 1.0){
		tmp = pow(16,count);
		one = 4.0 / ((8.0 * count) + 1.0);
		two = 2.0 / ((8.0 * count) + 4.0);
		three = 1.0 / ((8.0 * count) + 5.0);
		four = 1.0 / ((8.0 * count) + 6.0);
		fnl = tmp * (one - two - three - four);
		tot += fnl;
	}
	return tot;
}


int pi_bbp_terms(void){
	return (int)count;
}

