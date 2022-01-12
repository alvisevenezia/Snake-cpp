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

	int spawnSnake(int x, int y) {

		if (head == nullptr) {

			head = new snakePart();
			head->id = 1;
			head->next = nullptr;
			head->previous = nullptr;

		}

		head->x = x;
		head->y = y;

		grillen->mat[x + y * grillen->width] = 1;

		return 0;
	}

	int move(int* m);

	int translateMat(char c);
};


