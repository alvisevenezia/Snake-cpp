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

		layers.insert(layers.end(),new layer(sizel[id],id == 0? 1:sizel[id-1],id));
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

int * network::compute(matrice* input) {

	matrice* output{};

	for (int id = 0; id < layers.size();id++) {

		output = layers[id]->compute(id == 0 ? input->scaleMat(sizel[0]): output->scaleMat(sizel[id]));
		output->printMatFloat();
	}

	int d[4] = { 0,0,0,0 };

	int UP[4] = { 0,1,0,0 };
	int RIGHT[4] = { 0,0,1,0 };
	int DOWN[4] = { 0,0,0,1 };
	int LEFT[4] = { 1,0,0,0 };

	matrice* ref = new matrice(nullptr, 4, 1);
	ref->mat = { 0,1,0,0 };
	d[0] = minDistance(ref,output);
	ref->mat = { 0,0,1,0 };
	d[1] = minDistance(ref, output);
	ref->mat = { 0,0,0,1 };
	d[2] = minDistance(ref, output);
	ref->mat = { 1,0,0,0 };
	d[3] = minDistance(ref, output);

	int min = std::min(std::min(d[0], d[1]), std::min(d[2], d[3]));

	if (min == d[0])return UP;
	if (min == d[1])return RIGHT;
	if (min == d[2])return DOWN;
	if (min == d[3])return LEFT;
	return nullptr;
}