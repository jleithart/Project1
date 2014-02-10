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
}

void GeneticAlgorithm::PrintFitness(){
	searchPopulation->CalcFitness();
}
	
void GeneticAlgorithm::Search(){
	char tmp;
	double bestIndividual[DIMENSIONS];
	int bestIndex;
	//do this later
	//how many generations?

	for(int i = 0; i < NUM_GENERATIONS; i++){
		//Find the best individual and elitist them over
		bestIndex = GetBestIndividual();

		CopyIndividual(searchPopulation->GetIndividual(bestIndex), bestIndividual);
		selectedPopulation->AddIndividual(bestIndividual);
		selectedPopulation->AddIndividual(bestIndividual);

		for(int j = 0; j < MAX_POPULATION; j++){
			Select();
		}

		//we don't reinitialize selectedPopulation
		//searchPopulation = selectedPopulation;
		CopyPopulation(selectedPopulation, searchPopulation);
		selectedPopulation->ResetPopulation();
		if(DEBUG){
			//debugFile << "generation:: " << i << std::endl;
			searchPopulation->CalcFitness();
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

int GeneticAlgorithm::GetBestIndividual(){
	char tmp;
	int index = 0;
	for(int i = 1; i < MAX_POPULATION; i++){
		if(searchPopulation->GetFitness(index) > searchPopulation->GetFitness(i)){
			index = i;
		}
	}
	return index;
}

int GeneticAlgorithm::TourneySelect(){	//returns the index (max pop) of the winner

	int winningIndex = rand()%MAX_POPULATION;
	int tmpIndex;

	for(int i = 0; i < TourneySize; i++){
		tmpIndex = rand()%MAX_POPULATION;
		if(searchPopulation->GetFitness(tmpIndex) < searchPopulation->GetFitness(winningIndex) ){
			winningIndex = tmpIndex;
		}
	}
	return winningIndex;
}

void GeneticAlgorithm::Crossover(double [], double []){

}

void GeneticAlgorithm::Mutate(double individual[]){
	//adjust neighbors
	double changeValue = (searchFunction->range[HI_RANGE] - searchFunction->range[LOW_RANGE])/searchFunction->rateOfChange;
	for(int i = 0; i < DIMENSIONS; i++){
		int change = rand()%4;
		if(change <= 2){
			if(change == 1){
				individual[i] += changeValue;
				if(individual[i] > searchFunction->range[HI_RANGE]){
					individual[i] = searchFunction->range[HI_RANGE];
				}
			}
			else{
				individual[i] -= changeValue;
				if(individual[i] < searchFunction->range[LOW_RANGE])
					individual[i] = searchFunction->range[LOW_RANGE];
				}
		}
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
	std::cout << std::endl;
	for(int i = 0; i < DIMENSIONS; i++){
		std::cout << vector[i] << ", ";
	}
	std::cout << std::endl;
	if(DEBUG){
		std:: cin >> tmp;
	}
}

void GeneticAlgorithm::CopyPopulation(Population *i_population, Population *m_population){
	char tmp;
	for(int i = 0; i < MAX_POPULATION; i++){
		if(DEBUG){
			//std::cout << std::endl << "BEFORE COPY::" << std::endl;
			//PrintIndividual(i_population->GetIndividual(i));
			//PrintIndividual(m_population->GetIndividual(i));
		}
		CopyIndividual(i_population->GetIndividual(i), m_population->GetIndividual(i));
		if(DEBUG){
			//std::cout << "AFTER COPY::" << std::endl;
			//PrintIndividual(i_population->GetIndividual(i));
			//PrintIndividual(m_population->GetIndividual(i));
			//std::cin >> tmp;
		}
	}
}