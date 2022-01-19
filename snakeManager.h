#pragma once
#include "snake.h"
#include <vector>

class snakeManager {

public:

	std::vector<snake*> snakeVector;
	int popNumber;
	int size;
	std::vector<int> sizel;

	snakeManager(int popNumber,int size, std::vector<int> sizel);

	void createSnake();

	void initGrid(float val);

	void spawnSnake(int x, int y);

	void compute();

};