//DONE
#include <stdio.h>
#include <stdlib.h>
#include "mathlib.h"

static double count = 1.0;

//Created Exponant function as suggested on Discord
double exponant(double i){
	double val = 1.0;
	double ele = 1.0;
	
	while(val > EPSILON){
		val *= i / count;
		ele += val;
		count += 1.0;
	}
	return ele;
}

double e(void){
	return exponat(1);
}
int e_terms(void){
	return (int)count;
}

