#pragma once
#include "function.h"
class Sphere :
	public function
{
public:
	Sphere(void);
	~Sphere(void);
	double Fitness(double const []);
};

