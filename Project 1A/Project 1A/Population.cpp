#include "Population.h"


Population::Population(function *function)
{
	searchFunction = function;
	curIndex = 0;
}


Population::~Population(void)
{

}

double* Population::GetIndividual(const int index){
	assert(index >= 0 && index <= MAX_POPULATION);
	return population[index];
}


void Population::AddIndividual(double individual[DIMENSIONS]){
	char tmp;
	if(curIndex < MAX_POPULATION){
		CopyIndividual(individual, population[curIndex]);
		curIndex++;
	}
}

void Population::InitializePopulation(){
	for(int i = 0; i < MAX_POPULATION; i++){
		InitializeVector(population[i]);
		curIndex++;
	}
}

void Population::ResetPopulation(){
	for(int i = 0; i < MAX_POPULATION; i++){
		ResetIndividual(population[i]);
	}
	curIndex = 0;
}

void Population::ResetIndividual(double m_vector[DIMENSIONS]){
	for(int i = 0; i < DIMENSIONS; i++){
		m_vector[i] = 0.0;
	}
}


void Population::PrintPopulation(){
	for(int i = 0; i < MAX_POPULATION; i++){
		PrintVector(population[i]);
	}
}


void Population::PrintVector(const double i_vector[]){
	std::cout << "(";
	for(int i = 0; i < DIMENSIONS; i++){
		std::cout << i_vector[i] << ", ";
	}
	std::cout << ")" << std::endl;
}

double Population::GetFitness(const int index){
	assert(index >= 0 && index <= MAX_POPULATION);
	return fitnessPopulation[index];
}


void Population::InitializeVector(double m_array[DIMENSIONS]){
	double rand_val = 0.0;
	
	for(int i = 0; i < DIMENSIONS; i++){
		rand_val = searchFunction->range[LOW_RANGE] + static_cast<float>(std::rand())/(static_cast <float>(RAND_MAX/(searchFunction->range[HI_RANGE] - searchFunction->range[LOW_RANGE])));
		m_array[i] = rand_val;
	}
}

void Population::CalcFitness(){
	for(int i = 0; i < MAX_POPULATION; i++){
		fitnessPopulation[i] = searchFunction->Fitness(population[i]);
		std::cout << "Population:: " << i << " Fitness:: " << fitnessPopulation[i] << std::endl;
	}
}

void Population::CalcFitness(std::ofstream &file){
	for(int i = 0; i < MAX_POPULATION; i++){
		fitnessPopulation[i] = searchFunction->Fitness(population[i]);
		file << "Population:: " << i << " Fitness:: " << fitnessPopulation[i] << std::endl;
	}
	file << std::endl;
}

void Population::CopyIndividual(const double i_vector[], double m_vector[]){
	for(int i = 0; i < DIMENSIONS; i++){
		m_vector[i] = i_vector[i];
	}
}
