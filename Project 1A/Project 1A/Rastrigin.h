#pragma once
#include "function.h"
class Rastrigin :
	public function
{
public:
	Rastrigin(void);
	~Rastrigin(void);
	double Fitness(double const []);
};

