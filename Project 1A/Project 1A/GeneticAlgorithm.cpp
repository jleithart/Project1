#include "GeneticAlgorithm.h"


GeneticAlgorithm::GeneticAlgorithm(function * i_function)
{
	searchFunction = i_function;
	searchPopulation = new Population(searchFunction);
	selectedPopulation = new Population(searchFunction);
	TourneySize = i_function->TourneySize;
}

void GeneticAlgorithm::Init(){
	searchPopulation->InitializePopulation();
}


GeneticAlgorithm::~GeneticAlgorithm(void)
{
}

void GeneticAlgorithm::PrintPopulation(){
	searchPopulation->PrintPopulation();
	searchPopulation->CalcFitness();
}
	
void GeneticAlgorithm::Search(){
	char tmp;
	//do this later
	//how many generations?
	for(int i = 0; i < NUM_GENERATIONS; i++){
		for(int j = 0; j < MAX_POPULATION; j++){
			Select();
		}

		// NOT DEEP COPYING ONLY SHALLOW COPYING
		searchPopulation = selectedPopulation;
		//CopyPopulation(selectedPopulation, searchPopulation);
		PrintPopulation();
		if(DEBUG){
			std::cin >> tmp;
		}
	}
}

void GeneticAlgorithm::Select(){
	int firstWinnerIndex;
	int secondWinnerIndex;
	double firstParent[DIMENSIONS];
	double secondParent[DIMENSIONS];

	firstWinnerIndex = TourneySelect();
	secondWinnerIndex = TourneySelect();

	CopyIndividual(searchPopulation->GetIndividual(firstWinnerIndex), firstParent);
	CopyIndividual(searchPopulation->GetIndividual(secondWinnerIndex), secondParent);

	//crossover would be here

	Mutate(firstParent);
	Mutate(secondParent);

	selectedPopulation->AddIndividual(firstParent);
	selectedPopulation->AddIndividual(secondParent);
}

int GeneticAlgorithm::TourneySelect(){	//returns the index (max pop) of the winner

	int winningIndex = rand()%MAX_POPULATION;
	int tmpIndex;

	for(int i = 0; i < TourneySize; i++){
		tmpIndex = rand()%MAX_POPULATION;
		if(searchPopulation->GetFitness(winningIndex) > searchPopulation->GetFitness(tmpIndex)){
			winningIndex = tmpIndex;
		}
	}

	return winningIndex;
}

void GeneticAlgorithm::Crossover(double [], double []){

}

void GeneticAlgorithm::Mutate(double individual[]){
	//adjust neighbors
	int tmpIndex = rand()%DIMENSIONS;	//random index to mutate
	double changeValue = (searchFunction->range[HI_RANGE] - searchFunction->range[LOW_RANGE])/searchFunction->rateOfChange;
	int isPositive = rand()%2; //positive for negative
	if(isPositive){
		individual[tmpIndex] += changeValue;
		if(individual[tmpIndex] > searchFunction->range[HI_RANGE])
			individual[tmpIndex] = searchFunction->range[HI_RANGE];
	}
	else{
		individual[tmpIndex] -= changeValue;
		if(individual[tmpIndex] < searchFunction->range[LOW_RANGE])
			individual[tmpIndex] = searchFunction->range[LOW_RANGE];
	}
}

void GeneticAlgorithm::CopyIndividual(const double i_vector[], double m_vector[]){
	for(int i = 0; i < DIMENSIONS; i++){
		m_vector[i] = i_vector[i];
	}
}

void GeneticAlgorithm::PrintIndividual(const double vector[]){
	char tmp;
	if(DEBUG){
		std::cin >> tmp;
	}
	for(int i = 0; i < DIMENSIONS; i++){
		std::cout << vector[i] << std::endl;
	}
	if(DEBUG){
		std:: cin >> tmp;
	}
}

void GeneticAlgorithm::CopyPopulation(Population *i_population, Population *m_population){
	for(int i = 0; i < MAX_POPULATION; i++){
		CopyIndividual(i_population->GetIndividual(i), m_population->GetIndividual(i));
	}
}