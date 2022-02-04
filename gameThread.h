#pragma once
#include "snakeManager.h"
#include "computationThread.h"
#include "thread"

class gameThread {

public:
	bool cancel;
	int nthread;
	snakeManager* manager;
	std::thread* task;
	std::vector<computationThread*> threadList;

	gameThread(int popNumber, int size, std::vector<int> sizel);

	void runGame();

	void start();
};