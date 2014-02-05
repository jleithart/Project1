#pragma once
#define DIMENSIONS 30
#define LOW_RANGE 0
#define HI_RANGE 1

class function
{
public:
	double x_vector[DIMENSIONS];
	double range[2];
	double probabilityConstant;
	double rateOfChange;	//the higher the rate of change the lower the change actually happens
	double temperatureAdjustment;
	function(void);
	~function(void);
	virtual double Fitness(double const []) = 0;
};

