#include <vector>
#include "Snake.h"

Snake::Snake(network* network, matrice* grille) {

	Snake::networkn = network;
	Snake::grillen = grille;

}

void Snake::initializeNetwork(int size, std::vector<int> sizel) {

	Snake::networkn = new network(size,sizel);

}