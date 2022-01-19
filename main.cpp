#include "matrice.h"
#include "network.h"
#include "snake.h"
#include "snakeManager.h"

int main() {

	snakeManager* manager = new snakeManager(1,17, {17*17,50,25,4});

	manager->createSnake();
	manager->initGrid(0.0);
	manager->spawnSnake(8,8);
	manager->compute();	
	manager->snakeVector[0]->grillen->printMatInt();
	manager->compute();
	manager->snakeVector[0]->grillen->printMatInt();
	manager->compute();
	manager->snakeVector[0]->grillen->printMatInt();

}