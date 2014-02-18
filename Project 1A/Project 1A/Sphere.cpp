#include "Sphere.h"


Sphere::Sphere(void)
{
	range[LOW_RANGE] = -5.12;
	range[HI_RANGE] = 5.12;
	probabilityConstant = 10.0;
	rateOfChange = 1000.0;
	temperatureAdjustment = 0.001;
	TourneySize = 3;	//adjust the tourney size

	for(int i = 0; i < DIMENSIONS; i++)
		x_vector[i] = 0.0;
}


Sphere::~Sphere(void)
{
}

double Sphere::Fitness(double const i_vector[DIMENSIONS]){
	double sum = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum += i_vector[i]*i_vector[i];
	}

	return sum;
}
