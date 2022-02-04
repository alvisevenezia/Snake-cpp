#pragma once
#include <thread>
#include <mutex>
#include <assert.h>
#include "snakeManager.h"

class computationThread : public std::thread {

public: 

	int id;
	int offset;
	int size;
	bool cancel;
	int alive;
	snakeManager* manager;
	std::mutex lock;
	std::thread* task;

	computationThread(int id,int offset, int size);

	void run();

	void start();

	void pause();

	void stop();
};