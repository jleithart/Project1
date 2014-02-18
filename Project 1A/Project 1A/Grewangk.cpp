#include "Grewangk.h"


Grewangk::Grewangk(void)
{
	range[LOW_RANGE] = -600.0;
	range[HI_RANGE] = 600.0;
	probabilityConstant = 10.0;
	rateOfChange = 1000.0;
	temperatureAdjustment = 0.001;
	TourneySize = 3;	//adjust the tourney size

	for(int i = 0; i < DIMENSIONS; i++)
		x_vector[i] = 0.0;
}


Grewangk::~Grewangk(void)
{
}

double Grewangk::Fitness(const double i_vector[DIMENSIONS]){
	double product = 1.0;
	double sum = 1.0;
	for(int i = 0; i < DIMENSIONS; i++){
		for(int j = 0; j < DIMENSIONS; j++){
			product *= cos(i_vector[j]/sqrt(fabs((double)i)));
		}
		sum += (i_vector[i]*i_vector[i]/4000) - product;
	}

	return sum;
}