#pragma once
#include "matrice.h"

matrice::matrice(std::vector<float>* arg,int matWidth,int matHeight) {

	if (arg == nullptr) {

		width = matWidth;
		height = matHeight;
		mat = *(new std::vector<float>(matHeight * matWidth, 0.0));
		

	}
	else {

		width = matWidth;
		height = matHeight;
		mat = *arg;

	}

}

int minDistance(matrice* ref,matrice* B){
	
	if (ref->height != B->height && ref->width != B->width) {

		std::cout << "Matrice de taille différente\n" ;
		return -1;

	}

	int min = abs(B->mat[0] - ref->mat[0]);

	for (int id = 1; id < ref->height * ref->width; id++) {

		min = (abs(B->mat[id] - ref->mat[id])) < min ? abs(B->mat[id] - ref->mat[id]): min;

	}

	return min;
}

void matrice::randomlyFill(float min, float max) {

	srand(static_cast <unsigned> (time(0)));

	for (int id = 0; id < width * height; id++) {

		mat[id] = static_cast <float>(min) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / static_cast <float>((max - min))));

	}

}

//return a matrix with a new shape
matrice* matrice::transform(int width, int height)
{
	//check if the taget matrix's size isn't smaller than the initial matrix
	if (width * height < matrice::width * matrice::height) {

		//return error and exit
		printf("target matrix is too small");
		exit(1);
	}

	//create a new matrix
	matrice* m = new matrice(nullptr,width,height);

	//copy the data
	for (int id = 0; id < width * height; id++) {

		m->mat[id] = id > matrice::height * matrice::width ? 0 : matrice::mat[id];

	}

	//return the new matrix
	return m;
}


void matrice::fill(float val) {

	std::fill(mat.begin(), mat.end(), val);

}


void matrice::printMatInt() {

	int cpt = 0;

	for (float f : matrice::mat) {

		printf("%i ", (int)f);

		cpt++;
		if (cpt % width == 0)printf("\n");

	}

}

void matrice::printMatFloat() {

	int cpt = 0;

	for (float f : matrice::mat) {

		printf("%f ",f);

		cpt++;
		if (cpt % width == 0)printf("\n");

	}

}

std::vector<float> matrice::fillMatbyID(int x, int y, float val) {

	int pos = (int)(y * width) + x;

	mat[pos] = val;

	return mat;
}

matrice* matrice::scaleMat(int n) {

	int old = height;
	height *= n;

	for (int id = width; id < width * n; id++) {

		mat.insert(mat.end(),mat[id % width]);

	}

	return this;

}

matrice* multiplyMat(matrice* mat1, matrice* mat2) {

	if (mat1->width != mat2->height) {
		std::cout << "matrices does not have the same size";
		return nullptr;
	}

	matrice* matR = new matrice(nullptr, mat2->width, mat1->height);

	float somme = 0;

	for (int j = 0; j < mat1->height; j++) {

		for (int i = 0; i < mat2->width; i++) {

			somme = 0;

			for (int id = 0; id < mat1->width; id++) {

				somme += mat1->mat[j * mat1->width + id] * mat2->mat[id * mat2->width + i];

			}

			matR->mat[j * matR->width + i] = somme;

		}

	}

	return matR;

}

matrice* addMat(matrice* mat1, matrice* mat2) {

	if (mat1->width != mat2->width || mat1->height != mat2->height) {
		std::cout << "matrices does not have the same size";
		return nullptr;
	}

	matrice* matR = new matrice(nullptr, mat1->width, mat2->height);

	for (int j = 0; j < mat1->height; j++) {

		for (int i = 0; i < mat1->width; i++) {

			matR->mat[j * mat1->width + i] = mat1->mat[j * mat2->width + i] + mat2->mat[j * mat1->width + i];

		}
	}

	return matR;

}