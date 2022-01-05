#pragma once
#include "layer.h"

layer::layer(int size, int sizen,int id) {

	layer::id = id;
	layer::height = size;
	layer::width = sizen;
	initializeWeights(nullptr, nullptr);
	initializeBias(nullptr, nullptr);

}

int layer::initializeWeights(matrice* mat1, matrice* mat2) {

	if (mat1 == nullptr && mat2 == nullptr) {

		weight = new matrice(nullptr,width,height);
		weight->randomlyFill(0,sqrt(2/width*height));
	}else{

		matrice* matA = (mat1 == nullptr || mat2 == nullptr)? mat1 == nullptr ? mat2:mat1:mat1;
		matrice* matB = (mat1 == nullptr || mat2 == nullptr)?new matrice(nullptr, width, height):mat2;
		matB->randomlyFill(0, sqrt(2 / width * height));
		srand(static_cast <unsigned> (time(0)));
		
		for (int id = 0; id < width * height; id++) {
			
			weight[id] = (static_cast <float>(rand()) / static_cast <float>(RAND_MAX) > 0, 5) ? matA[id] : matB[id];

		}

	}
}

int layer::initializeBias(matrice* mat1, matrice* mat2) {

	if (mat1 == nullptr && mat2 == nullptr) {

		bias = new matrice(nullptr, 1, height);
		bias->randomlyFill(0, sqrt(2 / height));

	}
	else {

		matrice* matA = (mat1 == nullptr || mat2 == nullptr) ? mat1 == nullptr ? mat2 : mat1 : mat1;
		matrice* matB = (mat1 == nullptr || mat2 == nullptr) ? new matrice(nullptr, 1, height) : mat2;
		matB->randomlyFill(0, sqrt(2 / height));
		srand(static_cast <unsigned> (time(0)));

		for (int id = 0; id < height; id++) {

			weight[id] = (static_cast <float>(rand()) / static_cast <float>(RAND_MAX) > 0, 5) ? matA[id] : matB[id];

		}

	}

}

int layer::compute(matrice* input,matrice* output) {

	output = addMat(multiplyMat(weight, input), bias);

	return 0;

}