#pragma once
#include "matrice.h"
#include "mouvements.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

class layer {

public:
	matrice* weight;
	matrice* bias;
	int height;
	int width;
	int id; //util?

	layer(int size,int sizen,int id);

	matrice* getWeights();

	matrice* getBias();

	matrice* compute(matrice* input);

	matrice* normalizeOutput(matrice* output);

	int initializeWeights(matrice* mat1, matrice* mat2);

	int initializeBias(matrice* mat1, matrice* mat2);

};