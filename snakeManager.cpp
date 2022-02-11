#include "snakeManager.h"

snakeManager::snakeManager(int popNumber,int size, std::vector<int> sizel) {

	snakeManager::popNumber = popNumber;
	snakeManager::alive = popNumber;
	snakeManager::sizel = sizel;
	snakeManager::size = size;
}

//create one generation of snake of size specifed by popNumber
void snakeManager::createSnake() {

	//check if popNumber is initialized
	if (snakeManager::popNumber == NULL) {

		//print error and exit
		printf("PopNumber not initalized");
		exit(1);

	}

	snake* snaken;
	//create all the snakes and put them in snakeVector
	for (int id = 0; id < popNumber; id++) {

		//create the snake with a null network
		snaken = new snake(nullptr, new matrice(nullptr, size, size));
		snaken->id = id;
		
		//initialize snake's network
		snaken->initializeNetwork(sizel.size(),sizel);

		//insert the snake in the snake's vector
		snakeManager::snakeVector.insert(snakeManager::snakeVector.end(), snaken);

	}
}

//initiate the grid for all the snakes
void snakeManager::initGrid(float val) {

	snake* snake;

	//for each snake in the vector
	for (int id = 0; id < popNumber; id++) {

		//get the snake
		snake = snakeManager::snakeVector[id];
		snake->grillen->fill(val);
	}

}

//spawn all the snake
void snakeManager::spawnSnake(int x,int y) {

	snake* snake;

	//for each snake in the vector
	for (int id = 0; id < popNumber; id++) {

		//get the snake
		snake = snakeManager::snakeVector[id];

		//spawn the snake
		snake->spawnSnake(x, y);

	}

}

//compute the network for all the snakes
void snakeManager::compute() {

	snake* snake;

	//for each snake in the vector
	for (int id = 0; id < popNumber; id++) {

		//check if the snake is alive
		if (!snakeManager::snakeVector[id]->dead) {

			//get the snake
			snake = snakeManager::snakeVector[id];

			//make the network compute with the grid as the first input
			snake->move(snake->networkn->compute(snake->grillen->transform(1, size * size)));

			//compute the fitness of the snake
			snake->calculateFitness();

		}

		//if the is dead
		else {

			//decrement the alive snake's quantity 
			snakeManager::alive--;

			//if there no snake alive anymore stop to compute
			if (snakeManager::alive == 0)return;
		
		}

	}

}

bool compare(const snake* s1, const snake* s2) {

	return s1->fitness > s2->fitness;

}

//sort the vector of snakes
void snakeManager::sortSnakeVector() {

	//use standard function to sort the vector of snake using the given comparator function
	std::sort(snakeManager::snakeVector.begin(), snakeManager::snakeVector.end(),compare);

}

//comparator function to sort snake vector
bool snakeManager::comparator(const snake& fs, const snake& ss) {

	//return true if the left snake has a higher fitness than the one on the right
	return fs.fitness > ss.fitness;

}

//get the best snakes
std::vector<snake*> snakeManager::getBestSnakes(int quantity) {

	//sort the snake vector bases on the fitness of the snakes
	
	sortSnakeVector();

	//create a vector to store the bests snake
	std::vector<snake*> best = *(new std::vector<snake*>(quantity));

	for (int id = 0; id < quantity; id++) {

		best.push_back(snakeVector[id]);

	}


	return best;
}

//merge best snake to create the next population
void snakeManager::mergeSnakes() {

	//store the best snakes
	std::vector<snake*> best = getBestSnakes(10);

	//clear the curretn snakeVector
	snakeVector.clear();

	//reduce the size of the vector to save some memory (i guess)
	snakeVector.shrink_to_fit();

	//reserve de needed amount of memory
	snakeVector.reserve(popNumber);

	//init random 
	srand(time(nullptr));

	snake* snaken;

	for (int id = 0; id <= popNumber; id++) {

		//create a new snake
		snaken = new snake(nullptr, new matrice(nullptr, size, size));

		//initialize the network
		snaken->initializeNetwork(size, sizel);

		//merge network of 2 random snakes
		snaken->networkn->mergeNetworks(best[rand() % 10 + 1]->networkn, best[rand() % 10 + 1]->networkn);

		//put the new snake in the vector
		snakeVector.push_back(snaken);

	}

}