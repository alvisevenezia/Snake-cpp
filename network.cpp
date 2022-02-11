#pragma once
#include "network.h"

network::network(int size, std::vector<int> sizel) {

	network::sizel = sizel;
	network::size = size;

	initializeLayers();

}

void network::initializeLayers() {

	layers.reserve(size);

	for (int id = 0; id < size; id++) {

		layers.insert(layers.end(),new layer(sizel[id],id == 0? 17*17:sizel[id-1],id));
		layers[id]->initializeWeights(nullptr,nullptr);
		layers[id]->initializeBias(nullptr, nullptr);

	}

}

void network::mergeNetworks(network* n1, network* n2) {
	
	for (int id = 0; id < size; id++) {

		layers[id] = new layer(sizel[id], id == 0 ? 1 : sizel[id - 1], id);
		layers[id]->initializeWeights(n1->layers[id]->weight, n2->layers[id]->weight);
		layers[id]->initializeBias(n1->layers[id]->bias, n2->layers[id]->bias);

	}

}

//compute the netowrk with input matrix
int* network::compute(matrice* input) {

	matrice* output{};

	//iterate for each layer
	for (int id = 0; id < layers.size();id++) {

		//compute
		output = layers[id]->compute(id == 0 ? input: output);

		//print the results
		//output->printMatFloat();
		//std::cout << "\n" << std::endl;
	}

	//return output;
	//output->printMatFloat();
	 
	//define a buffer
	int d[4] = { 0,0,0,0 };

	//define the target output
	int UP[4] = { 0,1,0,0 };
	int RIGHT[4] = { 0,0,1,0 };
	int DOWN[4] = { 0,0,0,1 };
	int LEFT[4] = { 1,0,0,0 };


	matrice* ref = new matrice(nullptr, 1, 4);
	//get the distance between the result of the network and the intended result (interpreted as points in a n-dim space)
	ref->mat = { 0,1,0,0 };
	d[0] = minDistance(ref,output);
	ref->mat = { 0,0,1,0 };
	d[1] = minDistance(ref, output);
	ref->mat = { 0,0,0,1 };
	d[2] = minDistance(ref, output);
	ref->mat = { 1,0,0,0 };
	d[3] = minDistance(ref, output);

	//check the "closest" matrix
	int min = std::min(std::min(d[0], d[1]), std::min(d[2], d[3]));

	int* result = (int*) malloc(2*sizeof(int));

	//return the movement 
	if (min == d[0]) {

		result[0] = 0;
		result[1] = -1;

	}
	if (min == d[1]){
	
		result[0] = 1;
		result[1] = 0;

	}
	if (min == d[2]) {


			result[0] = 0;
			result[1] = -1;
	}
	if (min == d[3]) {

		result[0] = -1;
		result[1] = 0;


	}
	return result;
}