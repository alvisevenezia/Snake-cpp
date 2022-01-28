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


//activation function 
matrice* layer::ReLUActivationFunction(matrice* output) {

	//for each val of the matrix
	for (int id = 0; id < output->mat.size() ; id ++) {

		//ReLU function: x = max(0,x)
		output->mat[id] = output->mat[id] > 0 ? output->mat[id] : 0;

	}
	return output;
}

//initaliaze the weight's matrix
int layer::initializeWeights(matrice* mat1, matrice* mat2) {

	//if both input matrix are null, create a new one
	if (mat1 == nullptr && mat2 == nullptr) {

		weight = new matrice(nullptr,width,height);
		weight->randomlyFill(0,2);
	}else{

		//if one matrix is null, take the on the one that exist as the first matrix and a new one as the second
		//if both matrix exist, take both matrix as they are
		matrice* matA = (mat1 == nullptr || mat2 == nullptr)? mat1 == nullptr ? mat2:mat1:mat1;
		matrice* matB = (mat1 == nullptr || mat2 == nullptr)?new matrice(nullptr, width, height):mat2;

		//fill the newly created matrix 
		if(mat1 == nullptr || mat2 == nullptr)matB->randomlyFill(0,2);

		//initialize random function with the current host's time
		srand(static_cast <unsigned> (time(0)));
		
		for (int id = 0; id < width * height; id++) {
			
			//ramdomly take either the first or the second matrix's value for the new one
			weight[id] = (static_cast <float>(rand()) / static_cast <float>(RAND_MAX) > 0, 5) ? matA[id] : matB[id];

		}

	}

	return 0;

}

//initaliaze the bias's matrix
int layer::initializeBias(matrice* mat1, matrice* mat2) {

	//if both input matrix are null, create a new one
	if (mat1 == nullptr && mat2 == nullptr) {

		bias = new matrice(nullptr, 1, height);
		bias->randomlyFill(0,2);

	}
	else {

		//if one matrix is null, take the on the one that exist as the first matrix and a new one as the second
		//if both matrix exist, take both matrix as they are
		matrice* matA = (mat1 == nullptr || mat2 == nullptr) ? mat1 == nullptr ? mat2 : mat1 : mat1;
		matrice* matB = (mat1 == nullptr || mat2 == nullptr) ? new matrice(nullptr, 1, height) : mat2;

		//fill the newly created matrix 
		if(mat1 == nullptr || mat2 == nullptr)matB->randomlyFill(0, 2);

		//initialize random function with the current host's time
		srand(static_cast <unsigned> (time(0)));

		for (int id = 0; id < height; id++) {

			//ramdomly take either the first or the second matrix's value for the new one
			weight[id] = (static_cast <float>(rand()) / static_cast <float>(RAND_MAX) > 0, 5) ? matA[id] : matB[id];

		}

	}

	return 0;

}

matrice* layer::compute(matrice* input) {

	//pass trought ReLU the result of weight*input + bias
 	return ReLUActivationFunction(addMat(multiplyMat(weight, input), bias));

}