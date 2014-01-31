#include "Sphere.h"
#include "function.h"
#include <iostream>
#include <assert.h>
#include <time.h>

#define INF 10000000000.0


using namespace std;

void RandomizeVector(const function *, double []);
void PrintVector(const double []);
void HillClimb(function *, double []);
void SimulatedAnnealing(function *, double []);
void CopyVector(const double [], double []);
void AdjustNeighbor(const int, const bool, const function *, double []);
bool AcceptFitness(const double, const double, const double);

int main(){

	Sphere *search_sphere = new Sphere();
	char tmp;
	//randomize the seed
	srand(time(NULL));

	double minimizingSphereVector[DIMENSIONS];

	//grab array of random vectors
	RandomizeVector(search_sphere, minimizingSphereVector);
	// use separate function to find local minimum;

	PrintVector(minimizingSphereVector);
	cout << endl << search_sphere->Fitness(minimizingSphereVector) << endl;

	HillClimb(search_sphere, minimizingSphereVector);
	cout << endl;
	PrintVector(minimizingSphereVector);

	cout << endl << search_sphere->Fitness(minimizingSphereVector) << endl;
	cin >> tmp;

	return 0;
}

void RandomizeVector(const function *i_function, double m_array[DIMENSIONS]){
	double rand_val = 0.0;
	
	for(int i = 0; i < DIMENSIONS; i++){
		rand_val = i_function->range[LOW_RANGE] + static_cast<float>(rand())/(static_cast <float>(RAND_MAX/(i_function->range[HI_RANGE] - i_function->range[LOW_RANGE])));
		m_array[i] = rand_val;
	}
}

bool AcceptFitness(const double i_originalFitness, const double i_newFitness, const double i_temperature){

}

void SimulatedAnnealing(function * i_function, double m_vector[DIMENSIONS]){
	double min_fitness = i_function->Fitness(m_vector);
	double tmp_fitness;
	double neighbor[DIMENSIONS];
	int index = 0;
	float temperature = 100;
	bool raise = false;
	char tmp;

	//copy over the original array so we can hold the values
	CopyVector(m_vector, neighbor);

	//while Temperature > 0
	while(temperature > 0){
		//for T (temperature) = 100 to 0 step -.1
		//pick a neighbor of S1 called S2
		AdjustNeighbor(index, raise, i_function, neighbor);
		tmp_fitness = i_function->Fitness(neighbor);
		
		// if S2 is better replace
		if(tmp_fitness <= min_fitness){
			min_fitness = tmp_fitness;
			CopyVector(neighbor, m_vector);
		}
		//do if anyways if probability
		/*else if(FindProbability()probability works){
			min_fitness = tmp_fitness;
			CopyVector(neighbor, m_vector);
		}*/
		index = (index++) % DIMENSIONS;
		raise = !raise;
		// else with a probability replace them anyways
		//probability function is generally e^(-c(fitness1 - fitness 2)/T)

		temperature -= 0.1;
	}
	//pick a random solution S1
}

void HillClimb(function * i_function, double m_array[DIMENSIONS]){
	double min_fitness = i_function->Fitness(m_array);
	double tmp_fitness;
	double neighbor[DIMENSIONS];
	int index = 0;
	bool raise = false;
	char tmp;

	//copy over the original array so we can hold the values
	CopyVector(m_array, neighbor);


	while(index < 30){
		//grab neighbors
		AdjustNeighbor(index, raise, i_function, neighbor);
		tmp_fitness = i_function->Fitness(neighbor);
		//cout << "index:: " << index << " value:: " << neighbor[index] << " fitness " << tmp_fitness << endl;

		// check if the new vector is better than the original
		if(tmp_fitness <= min_fitness){
			min_fitness = tmp_fitness;
			CopyVector(neighbor, m_array);
			index = 0;
			raise = false;
		}
		else{
			if(raise == false){
				raise = true;
			}
			else{
				index++;
				raise = false;
			}
			//if not better use the old vector
			CopyVector(m_array, neighbor);
		}
	}
	
}

void CopyVector(const double i_original[DIMENSIONS], double m_replaced[DIMENSIONS]){
	for(int i = 0; i < DIMENSIONS; i++){
		m_replaced[i] = i_original[i];
	}
}

void AdjustNeighbor(const int index, const bool i_up, const function *i_function, double m_array[DIMENSIONS]){
	assert(index < 30 && index >= 0);
	//what's the rate of change?
	float changeValue = (i_function->range[HI_RANGE] - i_function->range[LOW_RANGE])/1000;

	// adjust up or down?
	if(!i_up){
		m_array[index] += changeValue;
		if(m_array[index] > i_function->range[HI_RANGE]){
			m_array[index] = i_function->range[HI_RANGE];
		}
	}
	else{
		m_array[index] -= changeValue;
		if(m_array[index] < i_function->range[LOW_RANGE])
			m_array[index] = i_function->range[LOW_RANGE];
	}

}

void PrintVector(const double i_array[DIMENSIONS]){
	cout << "( ";
	for(int i = 0; i < DIMENSIONS; i++){
		cout << i_array[i] << " ";
	}
	cout << ")" << endl;


}