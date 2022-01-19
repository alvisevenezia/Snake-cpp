#pragma once
#include <vector>
#include <stdlib.h>
#include <new>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

class matrice {

public:
	int width;
	int height;
	std::vector<float> mat;

	matrice(std::vector<float>* arg, int matWidth, int matHeight);

	void fill(float val);

	void printMatInt();

	matrice* scaleMat(int n);

	void printMatFloat();

	std::vector<float> fillMatbyID(int x, int y, float val);

	void randomlyFill(float min, float max);

	matrice* transform(int width, int height);
};



matrice* multiplyMat(matrice* mat1, matrice* mat2);

matrice* addMat(matrice* mat1, matrice* mat2);

int minDistance(matrice* ref, matrice* B);