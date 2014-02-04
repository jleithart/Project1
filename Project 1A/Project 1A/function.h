#pragma once
#define DIMENSIONS 30
#define LOW_RANGE 0
#define HI_RANGE 1

class function
{
protected:
	double x_vector[DIMENSIONS];
public:
	double range[2];
	double probabilityConstant;
	double rateOfChange;
	double temperatureAdjustment;
	function(void);
	~function(void);
	virtual double Fitness(double const []) = 0;
};

