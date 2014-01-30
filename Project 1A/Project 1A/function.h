#pragma once
#define DIMENSIONS 30
class function
{
protected:
	double range[2];
	double x_vector[DIMENSIONS];
public:
	function(void);
	~function(void);
	virtual double Fitness(double const []) = 0;
};

