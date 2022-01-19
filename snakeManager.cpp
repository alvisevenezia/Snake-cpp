#include "snakeManager.h"

snakeManager::snakeManager(int popNumber,int size, std::vector<int> sizel) {

	snakeManager::popNumber = popNumber;
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

		//get the snake
		snake = snakeManager::snakeVector[id];

		//make the network compute with the grille as the first input
		snake->move(snake->networkn->compute(snake->grillen->transform(1, size * size)));


	}

}