#pragma once
#include "globals.h"
#include "function.h"
class Population
{
private:
	double population[MAX_POPULATION][DIMENSIONS];
	function *searchFunction;
	int curIndex;	//for inserting a new individual on selection
public:
	double fitnessPopulation[MAX_POPULATION];

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
	void CalcFitness(std::ofstream &);

	void ResetPopulation();
	void ResetIndividual(double []);
};

