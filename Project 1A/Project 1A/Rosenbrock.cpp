#include "Rosenbrock.h"


Rosenbrock::Rosenbrock(void)
{
	range[LOW_RANGE] = -2.048;
	range[HI_RANGE] = 2.048;
	probabilityConstant = 10.0;
	rateOfChange = 1000.0;
	temperatureAdjustment = 0.001;
	TourneySize = 3;	//adjust the tourney size

	for(int i = 0; i < DIMENSIONS; i++)
		x_vector[i] = 1.0;
}


Rosenbrock::~Rosenbrock(void)
{
}

double Rosenbrock::Fitness(const double i_vector[DIMENSIONS]){
	double retval = 0.0;
	for(int i = 0; i < (DIMENSIONS - 1); i++){
		retval += 100*(i_vector[i+1] - i_vector[i]*i_vector[i]) + (i_vector[i] - 1)*(i_vector[i] - 1);
	}

	return retval;
}
