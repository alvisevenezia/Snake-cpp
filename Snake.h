#pragma once
#include "matrice.h"
#include "network.h"
#include "snakePart.h"

class snake {

public:

	int id;
	long score;
	matrice* grillen;
	network* networkn;
	snakePart* head;

	snake(network* network,matrice* grille);

	void initializeNetwork(int size, std::vector<int> sizel);

	void spawnSnake(int x, int y);

	int move(int* m);

	int translateMat(char c);
};


