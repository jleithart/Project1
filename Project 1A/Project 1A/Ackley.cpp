#include "Ackley.h"


Ackley::Ackley(void)
{
	range[LOW_RANGE] = -30.0;
	range[HI_RANGE] = 30.0;
	probabilityConstant = 10.0;
	rateOfChange = 1000.0;
	temperatureAdjustment = 0.001;
	TourneySize = 5;	//adjust the tourney size

	for(int i = 0; i < DIMENSIONS; i++)
		x_vector[i] = 0.0;
}


Ackley::~Ackley(void)
{
}

double Ackley::Fitness(const double i_vector[DIMENSIONS]){
	double retval;
	double sum1 = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum1 += i_vector[i]*i_vector[i];
	}
	retval = 20 + exp(1.0) - 20*exp(-0.2*sqrt(sum1/DIMENSIONS));

	double sum2 = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum2 += cos(2*3.14*i_vector[i]);
	}
	sum2 = sum2/DIMENSIONS;

	retval = retval - exp(sum2);

	return retval;

}
