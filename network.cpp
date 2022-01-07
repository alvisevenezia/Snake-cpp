#pragma once
#include "network.h"

int * network::compute(matrice* input) {

	matrice* output{};

	for (int id = 0; id < layers.size();id++) {

		output = layers[id]->compute(id == 0 ? input: output);

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