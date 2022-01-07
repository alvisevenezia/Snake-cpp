#pragma once
#include "matrice.h"
#include "mouvements.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

class layer {

private:
	matrice* weight;
	matrice* bias;
	int height;
	int width;
	int id; //util?

public:

	layer(int size,int sizen,int id);

	matrice* compute(matrice* input);

	int initializeWeights(matrice* mat1, matrice* mat2);

	int initializeBias(matrice* mat1, matrice* mat2);

};