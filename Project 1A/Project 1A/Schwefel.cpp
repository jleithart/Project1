#include "Schwefel.h"
#include <math.h>

#define SCHWEFEL_CONSTANT 418.9829

Schwefel::Schwefel(void)
{
	range[LOW_RANGE] = -512.03;
	range[HI_RANGE] = 511.97;
	probabilityConstant = 9.5;
	rateOfChange = 1020.0;
	temperatureAdjustment = 0.0001;
	TourneySize = 3;
	for(int i = 0; i  < DIMENSIONS; i++){
		x_vector[i] = -420.9687;
	}
}


Schwefel::~Schwefel(void)
{
}

double Schwefel::Fitness(double const i_vector[DIMENSIONS]){
	double sum = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum += i_vector[i]*(sin(sqrt(fabs(i_vector[i]))));
	}
	sum += SCHWEFEL_CONSTANT*DIMENSIONS;

	return sum;
}