//DONE
#include <stdio.h>
#include "mathlib.h"

static double count = 1.0;

//Created Exponant function as suggested on Discord
double exponant(double i){
	double val = 1.0;
	double ele = 1.0;
	for(;val > EPSILON; count += 1.0){
		val *= i / count;
		ele += val;
	}
	return ele;
}

double e(void){
	return exponant(1.0);
}
int e_terms(void){

	return (int)count;
}

