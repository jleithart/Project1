#include "Sphere.h"


Sphere::Sphere(void)
{
	range[0] = -5.12;
	range[1] = 5.12;
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
