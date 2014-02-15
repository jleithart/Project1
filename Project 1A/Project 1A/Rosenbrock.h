#pragma once
#include "function.h"

class Rosenbrock :
	public function
{
public:
	Rosenbrock(void);
	~Rosenbrock(void);
	double Fitness(double const []);
};

