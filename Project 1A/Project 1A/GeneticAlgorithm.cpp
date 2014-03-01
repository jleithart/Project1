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

	debugFile.open("debug.txt");
	debugFile << "Generation " << "Average " << "Best" << std::endl;
	for(int i = 0; i < NUM_GENERATIONS; i++){
		//Find the best individual and elitist them over
		bestIndex = GetBestIndividual();

		CopyIndividual(searchPopulation->GetIndividual(bestIndex), bestIndividual);
		selectedPopulation->AddIndividual(bestIndividual);
		selectedPopulation->AddIndividual(bestIndividual);

		for(int j = 0; j < MAX_POPULATION; j++){
			Select();
		}

		CopyPopulation(selectedPopulation, searchPopulation);
		selectedPopulation->ResetPopulation();

		//if(i % 10 == 0){
			std::cout << i << ":: ";
			debugFile << i << " ";
			GetBestAndAverage();
		//}
		
	}
	debugFile.close();
}

void GeneticAlgorithm::Select(){
	char tmp;
	int firstWinnerIndex;
	int secondWinnerIndex;
	double firstParent[DIMENSIONS];
	double secondParent[DIMENSIONS];

	firstWinnerIndex = TourneySelect();
	secondWinnerIndex = TourneySelect();

	CopyIndividual(searchPopulation->GetIndividual(firstWinnerIndex), firstParent);
	CopyIndividual(searchPopulation->GetIndividual(secondWinnerIndex), secondParent);

	Crossover(firstParent, secondParent);

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

void GeneticAlgorithm::Crossover(double first[DIMENSIONS], double second[DIMENSIONS]){
	double tmp;
	for(int i = 0; i < DIMENSIONS; i++){
		if(rand()%100 < 50){	//uniform distribution with some RNG
			double tmp = first[i];
			first[i] = second[i];
			second[i] = tmp;
		}
	}
}

void GeneticAlgorithm::Mutate(double individual[]){
	//adjust neighbors
	char tmp;
	double changeValue = (searchFunction->range[HI_RANGE] - searchFunction->range[LOW_RANGE])/searchFunction->rateOfChange;
	changeValue = static_cast<float>(std::rand())/(static_cast <float>(RAND_MAX/(changeValue*2))) - changeValue;
	int change;
	for(int i = 0; i < DIMENSIONS; i++){
		change = rand()%4;
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
		m_population->fitnessPopulation[i] = searchFunction->Fitness(i_population->GetIndividual(i));
		if(DEBUG){
			//std::cout << "AFTER COPY::" << std::endl;
			//PrintIndividual(i_population->GetIndividual(i));
			//PrintIndividual(m_population->GetIndividual(i));
			//std::cin >> tmp;
		}
	}
}

void GeneticAlgorithm::GetBest(){
	double bestVector[DIMENSIONS];
	CopyIndividual(searchPopulation->GetIndividual(GetBestIndividual()), bestVector);

	double sum = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum += ((bestVector[i] - searchFunction->x_vector[i])*(bestVector[i] - searchFunction->x_vector[i]));
	}
	sum = sum/DIMENSIONS;
	sum = sqrt(sum);
}

void GeneticAlgorithm::GetBestAndAverage(){
	double average = 0.0;
	for(int i = 0; i < MAX_POPULATION; i++){
		average += searchPopulation->fitnessPopulation[i];
	}
	average = average/MAX_POPULATION;

	double best = searchPopulation->fitnessPopulation[GetBestIndividual()];

	std::cout << average << " " << best << std::endl;
	debugFile << average << " " << best << std::endl;


}