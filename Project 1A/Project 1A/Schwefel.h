#pragma once
#include "function.h"

class Schwefel : public function
{
public:
	Schwefel(void);
	~Schwefel(void);
	double Fitness(double const []);
};

