#include "matrice.h"
#include "network.h"
#include "snake.h"

int main() {

	matrice *mat2 = new matrice(nullptr, 1, 4);
	mat2->mat = {6,5,4,3};
	(*mat2).printMatInt();

	std::cout << "\n";

	network* n = new network(3, {10,50,400});

	matrice* grille = new matrice(nullptr, 17, 17);
	grille->fill(0.0);
	grille->fillMatbyID(7, 8, -1);
	grille->printMatInt();

	std::cout << '\n' << std::endl;

	snake* s = new snake(n,grille);
	s->spawnSnake(8, 8);
	s->grillen->printMatInt();

	int m[2] = {-1,0};

	s->move(m);
	std::cout << '\n' << std::endl;
	s->grillen->printMatInt();
}