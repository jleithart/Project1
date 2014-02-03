#include "Schwefel.h"
#include <math.h>

#define SCHWEFEL_CONSTANT 418.9829

Schwefel::Schwefel(void)
{
	range[LOW_RANGE] = -512.03;
	range[HI_RANGE] = 511.97;
}


Schwefel::~Schwefel(void)
{
}

double Schwefel::Fitness(double const i_vector[DIMENSIONS]){
	double sum = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum += SCHWEFEL_CONSTANT*DIMENSIONS + i_vector[i]*(sin(sqrt(abs(i_vector[i]))));
	}

	return sum;
}