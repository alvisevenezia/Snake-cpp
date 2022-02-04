#include "matrice.h"
#include "network.h"
#include "snake.h"
#include "snakeManager.h"
#include "gameThread.h"

int main() {

	int nthread = std::thread::hardware_concurrency() > 1? std::thread::hardware_concurrency()-1 : 1;

	gameThread* game = new gameThread(1*nthread, 17, { 17 * 17,50,25,4 });

	/*snakeManager* manager = new snakeManager(1,17, {17*17,50,25,4});

	manager->createSnake();
	manager->initGrid(0.0);
	manager->spawnSnake(8,8);
	manager->compute();	
	manager->snakeVector[0]->grillen->printMatInt();
	manager->compute();
	manager->snakeVector[0]->grillen->printMatInt();
	manager->compute();
	manager->snakeVector[0]->grillen->printMatInt();*/

}