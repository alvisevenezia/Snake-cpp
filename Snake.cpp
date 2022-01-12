#include <vector>
#include "snake.h"

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

	snakePart* tampon = head;

	while (tampon != nullptr) {

		if (tampon->id == 1) {

			if (head->x + m[0] + head->y * grillen->width + m[1] >= 0 && head->x + m[0] + head->y * grillen->width + m[1] < grillen->height * grillen->width) {

				if (grillen->mat[head->x + m[0] + head->y * grillen->width + m[1]] <= 0) {

					snakePart* nh = new snakePart();
					nh->next = head;
					nh->previous = nullptr;
					nh->x = head->x + m[0];
					nh->y = head->y + m[1];
					nh->id = 1;
					head->previous = nh;

					if (grillen->mat[head->x + m[0] + head->y * grillen->width + m[1]] == -1) {

						snakePart* t = head;

						while (t->next != nullptr) {
							t->id++;
							t = t->next;
						}
						snakePart* ne = new snakePart();
						ne->id = t->id++;
						t->next = ne;
						ne->previous = t;

					}

					grillen->mat[head->x + m[0] + head->y * grillen->width + m[1]] = 1;

				} 
				else {

					printf("GAME OVER");
					return 0;

				}

			}

		}
		else {

			if (tampon->next == nullptr) {

				tampon->previous->next = nullptr;
				grillen->mat[tampon->x + tampon->y * grillen->width] = 0;
				free(tampon);
				return 0;
			}

			tampon->id++;

			grillen->mat[tampon->x+ tampon->y * grillen->width] = tampon->id--;

			tampon = tampon->next;

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