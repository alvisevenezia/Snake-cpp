#include "computationThread.h"


computationThread::computationThread(int id, int offset, int size) {

	computationThread::id = id;
	computationThread::offset = offset;
	computationThread::size = size;
	computationThread::task = nullptr;
	computationThread::cancel = false;
	computationThread::alive = size;
}

//run function
void computationThread::run() {

	if (cancel || alive <= 0) {
		//stop the thread
		std::terminate;
	}
	//for each snake of the batch
	for (int id = 0; id < size; id++) {

		//check if the snake is dead
		if (!manager->snakeVector[offset + id]->dead) {
			
			//move the snakedecrement the alive quantity is the snake dies
			if (manager->snakeVector[offset + id]->move(manager->snakeVector[offset + id]->networkn->compute(manager->snakeVector[offset + id]->grillen)) == -1) alive--;
		}
	}

}

//start the thread
void computationThread::start() {

	//create a new thread if it's null
	if (computationThread::task == nullptr) {


	}

}

//stop the thread
void computationThread::stop(){

	cancel = true;

}