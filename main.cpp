#include "matrice.h"
#include "network.h"

int main() {

	matrice *mat2 = new matrice(nullptr, 4, 1);
	mat2->mat = {6,5,4,3};
	(*mat2).printMatInt();

	std::cout << "\n";

	network* n = new network(3, {4,5,7});

	n->layers[0]->weight->printMatFloat();
	printf("\n\n\n");
	n->layers[0]->bias->printMatFloat();
	printf("\n\n\n");
	n->layers[1]->weight->printMatFloat();
	printf("\n\n\n");
	n->layers[1]->bias->printMatFloat();
	printf("\n\n\n");
	n->layers[2]->weight->printMatFloat();
	printf("\n\n\n");
	n->layers[2]->bias->printMatFloat();
	printf("\n\n\n");

	int* output = n->compute(mat2);

	for (int id = 0; id < 4;id++) {

		printf("%i\n", output[id]);

	}
	
}