#pragma once
#include "layer.h"
#include "mouvements.h"
#include <vector>
#include <algorithm>

class network {

private:
	
	std::vector<layer*> layers;
	std::vector<int>sizel;

public:

	network(int size,std::vector<int> sizel,bool dor);//size is for number of laye, sizel is for size of each layer and dor is for ramdomly initialize layer

	int* compute(matrice* input);

};