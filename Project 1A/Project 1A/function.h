#pragma once
#include "globals.h"

class function
{
public:
	int TourneySize;
	double x_vector[DIMENSIONS];
	double range[2];
	double probabilityConstant;
	double rateOfChange;	//the higher the rate of change the lower the change actually happens
	double temperatureAdjustment;
	function(void);
	~function(void);
	virtual double Fitness(double const []) = 0;
};

