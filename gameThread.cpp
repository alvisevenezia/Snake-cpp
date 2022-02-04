#include "gameThread.h"

gameThread::gameThread(int popNumber, int size, std::vector<int> sizel) {

	manager = new snakeManager(popNumber,size,sizel);
	cancel = false;

	//count the quantity of thread available
	nthread = std::thread::hardware_concurrency()> 1 ? std::thread::hardware_concurrency()-1 : 1;

	//initialize the threadList
	threadList = *(new std::vector<computationThread*>(nthread));

	//size for the batch
	int sizeBatch = manager->popNumber / nthread;

	//for each thread to create
	for (int n = 0; n < nthread; n++) {

		//create the worker thread
		threadList.push_back(new computationThread(n,n* sizeBatch, sizeBatch));

	}
}

void gameThread::runGame() {

	

}

void gameThread::start() {
	task = &(std::thread(&runGame,this));

	//create snakes
	manager->createSnake();
	manager->initGrid(0.0);
	manager->spawnSnake(8, 8);

}