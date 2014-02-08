#pragma once
#include "globals.h"
class Individual
{
private:
	double individual_vector[DIMENSIONS];
public:
	Individual();
	Individual(double max, double min);
	~Individual(void);
};

