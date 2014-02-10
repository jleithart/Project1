#pragma once
#include "globals.h"
#include "function.h"
class Population
{
private:
	double population[MAX_POPULATION][DIMENSIONS];
	double fitnessPopulation[MAX_POPULATION];
	function *searchFunction;
	int curIndex;	//for inserting a new individual on selection
public:
	Population(function *);
	~Population(void);
	void InitializePopulation();
	void PrintPopulation();
	void PrintVector(const double []);
	void InitializeVector(double []);

	double GetFitness(const int);

	double* GetIndividual(const int);
	void AddIndividual(double []);
	void CopyIndividual(const double[], double []);

	void CalcFitness();

	void ResetPopulation();
	void ResetIndividual(double []);
};

