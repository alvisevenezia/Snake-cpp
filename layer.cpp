#pragma once
#include "layer.h"

layer::layer(int size, int sizen,int id) {// size is for the number fo neuron of the actual layer
	// and sizen is for the size of the id-1 layer

	layer::id = id;
	layer::height = size;
	layer::width = sizen;
	initializeWeights(nullptr, nullptr);
	initializeBias(nullptr, nullptr);

}

matrice* layer::getWeights() {

	return layer::weight;

}

matrice* layer::getBias() {

	return layer::bias;

}

matrice* layer::normalizeOutput(matrice* output) {

	for (float f : output->mat) {

		f = f > 0 ? f : 0;

	}
	return output;
}

int layer::initializeWeights(matrice* mat1, matrice* mat2) {

	if (mat1 == nullptr && mat2 == nullptr) {

		weight = new matrice(nullptr,width,height);
		weight->randomlyFill(0,sqrtf(2.0/ (static_cast<double>(width)* static_cast<double>(height))));
	}else{

		matrice* matA = (mat1 == nullptr || mat2 == nullptr)? mat1 == nullptr ? mat2:mat1:mat1;
		matrice* matB = (mat1 == nullptr || mat2 == nullptr)?new matrice(nullptr, width, height):mat2;
		matB->randomlyFill(0, sqrtf(2.0 / (static_cast<double>(width) * static_cast<double>(height))));
		srand(static_cast <unsigned> (time(0)));
		
		for (int id = 0; id < width * height; id++) {
			
			weight[id] = (static_cast <float>(rand()) / static_cast <float>(RAND_MAX) > 0, 5) ? matA[id] : matB[id];

		}

	}

	return 0;

}

int layer::initializeBias(matrice* mat1, matrice* mat2) {

	if (mat1 == nullptr && mat2 == nullptr) {

		bias = new matrice(nullptr, 1, height);
		bias->randomlyFill(0, sqrtf(2.0 / static_cast<double>(height)));

	}
	else {

		matrice* matA = (mat1 == nullptr || mat2 == nullptr) ? mat1 == nullptr ? mat2 : mat1 : mat1;
		matrice* matB = (mat1 == nullptr || mat2 == nullptr) ? new matrice(nullptr, 1, height) : mat2;
		matB->randomlyFill(0, sqrtf(2.0 / static_cast<double>(height)));
		srand(static_cast <unsigned> (time(0)));

		for (int id = 0; id < height; id++) {

			weight[id] = (static_cast <float>(rand()) / static_cast <float>(RAND_MAX) > 0, 5) ? matA[id] : matB[id];

		}

	}

	return 0;

}

matrice* layer::compute(matrice* input) {

 	return normalizeOutput(addMat(multiplyMat(weight, input), bias));

}