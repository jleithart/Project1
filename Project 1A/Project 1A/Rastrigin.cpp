#include "Rastrigin.h"


Rastrigin::Rastrigin(void)
{
	range[LOW_RANGE] = -5.12;
	range[HI_RANGE] = 5.12;
	probabilityConstant = 10.0;
	rateOfChange = 1000.0;
	temperatureAdjustment = 0.001;
	TourneySize = 5;	//adjust the tourney size

	for(int i = 0; i < DIMENSIONS; i++)
		x_vector[i] = 0.0;
}


Rastrigin::~Rastrigin(void)
{
}

double Rastrigin::Fitness(const double i_vector[DIMENSIONS]){
	double retval = 10*DIMENSIONS;
	double sum = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum += i_vector[i]*i_vector[i] - 10*cos(2*3.14*i_vector[i]);
	}
	retval += sum;

	return retval;

}