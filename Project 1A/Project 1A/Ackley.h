#pragma once
#include "function.h"
class Ackley :
	public function
{
public:
	Ackley(void);
	~Ackley(void);
	double Fitness(double const []);
};

