#pragma once
#include "matrice.h"
#include "network.h"

class Snake {

private:

	int id;
	long score;
	matrice* grillen;
	network* networkn;

public:

	Snake(network* network,matrice* grille);

	void initializeNetwork(int size, std::vector<int> sizel);

	matrice* getGrid();

	network* getNetwork();

};


