#include "matrice.h"

int main() {

	int width = 5;
	int height = 2;

	matrice* mat = new matrice(nullptr,width, height);
	mat->randomlyFill(0, 5);
	(*mat).printMatInt();

	std::cout << "\n";

	matrice *mat2 = new matrice(nullptr, 3, width);
	mat2->mat = {6,5,4,3,2,4,5,6,7,8,9,6,7,8,9};
	(*mat2).printMatInt();

	std::cout << "\n";

	matrice* matR = multiplyMat(mat, mat2);
	(*matR).printMatInt();

	std::cout << "\n";	

	matrice* matR2 = addMat(mat, mat);
	(*matR2).printMatInt();
		
	printf("\n\n\n");

}