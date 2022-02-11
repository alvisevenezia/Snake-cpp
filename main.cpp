#include "matrice.h"
#include "network.h"
#include "snake.h"
#include "snakeManager.h"
#include "gameThread.h"

std::vector<std::thread> threadList;
bool cancelGame = false;
bool compute = false;
int sizeBatch;
std::vector<int> alive;
int alivea;


//game function
void game(snakeManager* manager,int nThread) {

	//check if the programm should stop
	if (cancelGame)std::terminate;

	//check is all snakes are dead
	for (int id = 0; id < nThread; id++) {

		alivea += alive[id];

	}

	//if so
	if (alivea <= 0) {

		//stop the worker threads 
		compute = false;

		//merge the snakes
		manager->mergeSnakes();

		//reset the alive value for each worker thread
		for (int id = 0; id < nThread; id++) {

			alive[id] = sizeBatch;

		}

		manager->createSnake();
		manager->initGrid(0.0);
		manager->spawnSnake(8, 8);

		//start the worker threads
		compute = true;
	}


}

//function for worker thread
void worker(snakeManager* manager,int offset, int size,int id,int* tampon) {

	//check if the thread should compute
	if (compute) {

		//start for the 'offset+size'th snake and stop 'size' snake after
		for (int id = offset; id < offset + size; id++) {

			//check if snake is dead
			if (!manager->snakeVector[id]->dead) {

				printf("%d",id);

				//move the snake
				*tampon = manager->snakeVector[id]->move(manager->snakeVector[id]->networkn->compute(manager->snakeVector[id]->grillen->transform(1,17*17)));

				//check is the snake is dead
				if (*tampon == -1) {

					alive[id]--;
					manager->snakeVector[id]->dead = true;
				}

			}

		}
	

	}
}

int main() {

	//count how muhc thrad are available
	int nthread = std::thread::hardware_concurrency() > 1? std::thread::hardware_concurrency()-1 : 1;

	//create the snakeManager
	snakeManager* manager = new snakeManager(100 * nthread, 17, { 17 * 17,50,25,4 });

	//create snake, grid and spawn snake
	manager->createSnake();
	manager->initGrid(0.0);
	manager->spawnSnake(8, 8);

	//batch size
	sizeBatch = manager->popNumber / nthread;


	alive = *(new std::vector<int>(nthread,0));

	//create all worker threads
	for (int id = 0; id < nthread; id++) {

		int tampon = 0;

		threadList.push_back(std::thread(worker,manager, id + sizeBatch, sizeBatch, id, &tampon));

	}

	//make workers compute
	compute = true;

	//start the game thread
	std::thread task = std::thread(game,manager,nthread);


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