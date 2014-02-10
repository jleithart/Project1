#include "Sphere.h"
#include "Schwefel.h"
#include "function.h"
#include "GeneticAlgorithm.h"





using namespace std;

void RandomizeVector(const function *, double []);
void PrintVector(const double []);
void HillClimb(function *, double []);
void SimulatedAnnealing(function *, double []);
void CopyVector(const double [], double []);
void AdjustNeighbor(const int, const bool, const function *, const float, double []);
void AdjustNeighborSA(const function *, const float, double []);
bool AcceptFitness(const double, const double, const double, const double);

void StandardDeviation(const function *, const double []);

int main(){

	Sphere *search_sphere = new Sphere();
	Schwefel *search_schwefel = new Schwefel();
	char tmp;

	if(DEBUG){
		//debugFile.open("debug.txt");
	}
	//randomize the seed
	srand(time(NULL));

	GeneticAlgorithm *GA = new GeneticAlgorithm(search_sphere);
	GA->Init();
	//GA->PrintPopulation();
	GA->PrintFitness();

	//cout << "wop wop" << endl;
	GA->Search();

	double SphereVector[DIMENSIONS];
	double tmpSphereVector[DIMENSIONS];
	double SchwefelVector[DIMENSIONS];
	double tmpSchwefelVector[DIMENSIONS];


	/*cout << "SPHERE VECTORS!!" << endl;
	//randomize Sphere vector
	RandomizeVector(search_sphere, SphereVector);
	CopyVector(SphereVector, tmpSphereVector);

	cout << "HILL CLIMBING" << endl;
	PrintVector(SphereVector);
	cout << endl << search_sphere->Fitness(SphereVector) << endl;
	HillClimb(search_sphere, SphereVector);
	cout << endl;
	PrintVector(SphereVector);
	cout << endl << search_sphere->Fitness(SphereVector) << endl;
	StandardDeviation(search_sphere, SphereVector);

	//simulated annealing
	cout << "SA" << endl;
	PrintVector(tmpSphereVector);
	cout << endl << search_sphere->Fitness(tmpSphereVector) << endl;
	SimulatedAnnealing(search_sphere, tmpSphereVector);
	cout << endl;
	PrintVector(tmpSphereVector);
	cout << endl << search_sphere->Fitness(tmpSphereVector) << endl;
	StandardDeviation(search_sphere, tmpSphereVector);


	cout << "SCHWEFEL VECTORS!!" << endl;
	//randomize Schwefel vector
	RandomizeVector(search_schwefel, SchwefelVector);
	CopyVector(SchwefelVector, tmpSchwefelVector);
	//RandomizeVector(search_schwefel, schefelSAVector);

	PrintVector(SchwefelVector);
	cout << endl << search_schwefel->Fitness(SchwefelVector) << endl;
	HillClimb(search_schwefel, SchwefelVector);
	cout << endl;
	PrintVector(SchwefelVector);
	cout << endl << search_schwefel->Fitness(SchwefelVector) << endl;
	StandardDeviation(search_schwefel, SchwefelVector);

	cout << "SA on same" << endl;
	PrintVector(tmpSchwefelVector);
	cout << endl << search_schwefel->Fitness(tmpSchwefelVector) << endl;
	SimulatedAnnealing(search_schwefel, tmpSchwefelVector);
	cout << endl;
	PrintVector(tmpSchwefelVector);
	cout << endl << search_schwefel->Fitness(tmpSchwefelVector) << endl;
	StandardDeviation(search_schwefel, tmpSchwefelVector);*/

	// use separate function to find local minimum;

	GA->PrintFitness();

	cin >> tmp;
	if(DEBUG){
		//debugFile.close();
	}

	return 0;
}

void StandardDeviation(const function *i_function, const double i_vector[DIMENSIONS]){
	double sum = 0.0;
	for(int i = 0; i < DIMENSIONS; i++){
		sum += ((i_vector[i] - i_function->x_vector[i])*(i_vector[i] - i_function->x_vector[i]));
	}
	sum = sum/DIMENSIONS;
	sum = sqrt(sum);
	cout << "The Standard Deviation is " << sum << endl;
}

void RandomizeVector(const function *i_function, double m_array[DIMENSIONS]){
	double rand_val = 0.0;
	
	for(int i = 0; i < DIMENSIONS; i++){
		rand_val = i_function->range[LOW_RANGE] + static_cast<float>(rand())/(static_cast <float>(RAND_MAX/(i_function->range[HI_RANGE] - i_function->range[LOW_RANGE])));
		m_array[i] = rand_val;
	}
}

bool AcceptFitness(const double i_originalFitness, const double i_newFitness, const double i_temperature, const double i_probabilityConstant){
	char debug;
	double threshold = ((double) rand())/(RAND_MAX + 1);
	double probability = exp(-i_probabilityConstant*((i_newFitness - i_originalFitness)/i_temperature));
	if(i_newFitness < i_originalFitness){
		return true;
	}
	else{
		if(DEBUG){
			//debugFile << "threshold:: " << threshold << " probability:: " << probability << endl;
		}
		//cout << "threshold:: " << threshold << " probability:: " << probability << endl;
		//cin >> debug;
		return (threshold < probability);
	}
}

void AdjustNeighborSA(const function *i_function, const float i_rateofchange, double m_array[DIMENSIONS]){
	//what's the rate of change?
	double changeValue = (i_function->range[HI_RANGE] - i_function->range[LOW_RANGE])/i_rateofchange;
	//double changeValue = 0.01;

	for(int i = 0; i < DIMENSIONS; i++){
		int change = rand()%4;
		if(change <= 2){
			if(change == 1){
				m_array[i] += changeValue;
				if(m_array[i] > i_function->range[HI_RANGE]){
					m_array[i] = i_function->range[HI_RANGE];
				}
			}
			else{
				m_array[i] -= changeValue;
				if(m_array[i] < i_function->range[LOW_RANGE])
					m_array[i] = i_function->range[LOW_RANGE];
				}
		}
	}
}

void SimulatedAnnealing(function * i_function, double m_vector[DIMENSIONS]){
	double min_fitness = i_function->Fitness(m_vector);
	double tmp_fitness;
	double neighbor[DIMENSIONS];
	int index = 0;
	double temperature = 100.0;
	double rateOfChange;
	bool raise = false;
	//char tmp;

	//copy over the original array so we can hold the values
	CopyVector(m_vector, neighbor);

	//while Temperature > 0
	while(temperature > 0){
		//for T (temperature) = 100 to 0 step -.1
		//pick a neighbor of S1 called S2
		rateOfChange = i_function->rateOfChange/temperature;
		AdjustNeighborSA(i_function, rateOfChange, neighbor);
		tmp_fitness = i_function->Fitness(neighbor);
		
		// if S2 is better replace
		//cout << "tmp_fitness:: " << tmp_fitness << " min_fitness:: " << min_fitness << endl;
		if(AcceptFitness(min_fitness, tmp_fitness, temperature, i_function->probabilityConstant) ){
			if(DEBUG){
				//debugFile << "tmp_fitness:: " << tmp_fitness << " min_fitness:: " << min_fitness << endl;
			}
			min_fitness = tmp_fitness;
			CopyVector(neighbor, m_vector);
		}
		else{
			//TODO FIX RATE OF CHANGE
			CopyVector(m_vector, neighbor);
		}
		// else with a probability replace them anyways
		//probability function is generally e^(-c(fitness1 - fitness 2)/T)

		temperature -= i_function->temperatureAdjustment;
	}
	//pick a random solution S1
}

void HillClimb(function * i_function, double m_array[DIMENSIONS]){
	double min_fitness = i_function->Fitness(m_array);
	double tmp_fitness;
	double neighbor[DIMENSIONS];
	int index = 0;
	bool raise = false;
	float rateOfChange = 1000.0;
	char tmp;

	//copy over the original array so we can hold the values
	CopyVector(m_array, neighbor);


	while(index < 30){
		//grab neighbors
		//AdjustNeighborSA(i_function, rateOfChange, neighbor);
		AdjustNeighbor(index, raise, i_function, rateOfChange, neighbor);
		tmp_fitness = i_function->Fitness(neighbor);
		//cout << "index:: " << index << " value:: " << neighbor[index] << " fitness " << tmp_fitness << endl;

		// check if the new vector is better than the original
		if(tmp_fitness < min_fitness){
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

void AdjustNeighbor(const int index, const bool i_up, const function *i_function, const float i_rateofchange, double m_array[DIMENSIONS]){
	assert(index < 30 && index >= 0);
	//what's the rate of change?
	double changeValue = (i_function->range[HI_RANGE] - i_function->range[LOW_RANGE])/i_rateofchange;

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