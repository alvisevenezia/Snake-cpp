#pragma once
#include "layer.h"
#include "mouvements.h"
#include <vector>
#include <algorithm>

class network {

public:
	
	int size;
	std::vector<layer*> layers;
	std::vector<int>sizel;

	network(int size,std::vector<int> sizel);//size is for number of layer, sizel is for size of each layer and ri is for ramdomly initialize layer

	void initializeLayers();

	void mergeNetworks(network* n1, network* n2);

	char compute(matrice* input);

};