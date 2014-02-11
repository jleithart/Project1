#pragma once
#include "function.h"
#include "Population.h"

class GeneticAlgorithm
{
private:
	function *searchFunction;
	Population *searchPopulation;
	Population *selectedPopulation;

	std::ofstream debugFile;

	int TourneySize;

public:
	
	void PrintPopulation();
	void PrintFitness();
	void Init();
	
	void Search();
	GeneticAlgorithm(function *);
	~GeneticAlgorithm(void);

	void Select();
	int TourneySelect();	//returns the index (max pop) of the winner
	int GetBestIndividual(); //returns the index of the best individual for elitism
	void Crossover(double [], double []);
	void Mutate(double []);

	void CopyIndividual(const double[], double []);
	void CopyPopulation(Population *, Population*);
	void PrintIndividual(const double []);	//for debugging

	void GetBest();	//returns the best 
};

