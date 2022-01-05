#pragma once
#include "layer.h"
#include "mouvements.h"
#include <vector>

class network {

private:
	
	std::vector<layer*> layer;

public:

	network(int size,std::vector<int> sizel,bool dor);//size is for number of laye, sizel is for size of each layer and dor is for ramdomly initialize layer

	mouvements compute(matrice* input);

};