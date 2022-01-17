#include <vector>
#include "snake.h"
#include <assert.h>

snake::snake(network* network, matrice* grille) {

	snake::networkn = network;
	snake::grillen = grille;
	snake::head = new snakePart();
	snake::head->id = 1;
	snake::head->next = nullptr;

}

void snake::initializeNetwork(int size, std::vector<int> sizel) {

	snake::networkn = new network(size, sizel);


}

int snake::move(int *m) {

	assert(head != nullptr);

	int tx = head->x + m[0];
	int ty = head->y + m[1];

	snakePart* tampon;
	
	//check if the snake snake is about to move out of the game
	if (0 <= tx && tx <= grillen->width && 0 <= ty && ty <= grillen->height) {

		//check if the snake is about to eat an apple
		if (grillen->mat[ty * grillen->width + tx] == -1) {

			//we add a new snakePart as a new head and we shift all id by one
			
			head->previous = new snakePart();
			head->previous->next = head;
			head->previous->previous = nullptr;
			head->previous->id = 1;
			head->previous->x = tx;
			head->previous->y = ty;
			grillen->mat[ty * grillen->width + tx] = 1;
			
			head = head->previous;

			tampon = head;

			//shift all the ids
			while (tampon->next != nullptr) {
				
				tampon = tampon->next;
				tampon->id = tampon->id++;
				grillen->mat[tampon->y * grillen->width + tampon->x] = tampon->id;
			
			}

		}
		//check if the snake if about to move on a free place
		else if(grillen->mat[ty * grillen->width + tx] == 0){

			tampon = head;
			//go to the tail
			while (tampon->next != nullptr)tampon = tampon->next;

			//delete the tail on the grid
			grillen->mat[tampon->y * grillen->width + tampon->x] = 0;

			//upadte the location of each snake part and update the grid
			while (tampon != head) {

				tampon->x = tampon->previous->x;
				tampon->y = tampon->previous->y;
				grillen->mat[tampon->y * grillen->width + tampon->x] = tampon->id;
				tampon = tampon->previous;
			}

			//move the head
			grillen->mat[ty * grillen->width + tx] = 1;
			head->x = tx;
			head->y = ty;


		}

	}

	return -1;
}

int snake::translateMat(char c) {

	switch (c)
	{
	case 'U':

		for (int id = 0; id < grillen->height * (grillen->width); id++) {

			grillen->mat[id] = (id < grillen->height * (grillen->width-1))? grillen->mat[id + grillen->width] : 0;

		}

		return 0;

	case 'L':

		for (int id = 0; id < grillen->height * (grillen->width); id++) {

			grillen->mat[id] =((id+1) % grillen->width == 0) ? 0 : id  < grillen->height* (grillen->width) ? grillen->mat[id + 1] : 0;

		}

		return 0;

	case 'D':

		for (int id = grillen->height * (grillen->width-1); id >= 0; id--) {

			grillen->mat[id] = (id < grillen->width) ? 0: grillen->mat[id-grillen->width];

		}

		return 0;

	case 'R':

		for (int id = grillen->height * grillen->width-1; id > 0; id--) {

			grillen->mat[id] = ((id) % grillen->width == 0) ? 0 : grillen->mat[id-1];

		}

		grillen->mat[0] = 0;

		return 0;
	default:

		return -1;
		break;
	}
}