#include "layer.h"
#include "stdlib.h"
#include "time.h"
#include "iostream"
#include <cmath>
#include <random>

layer::~layer(){

    free(weights);
    free(bias);
}

void layer::initLayer(int size,int inputSize){

    //initialize wieghts' array and bias' array
    layer::weights = (float*)calloc(inputSize*size,sizeof(float));
    layer::bias = (float*)calloc(size,sizeof(float));

    layer::size = size;
    layer::inputSize = inputSize;
    
    //rand() initilize weight
    for(int i = 0; i< inputSize*size;i++){

        layer::weights[i] = (static_cast<float>( rand()) / static_cast<float>(RAND_MAX))*2-1;

    }

    //rand() initialize bias
    for(int i = 0; i<size;i++){

        layer::bias[i] = (static_cast<float>( rand()) / static_cast<float>(RAND_MAX))*2-1;

    }

}

float* layer::compute(float* input,int id){

    //initialize array for data
    float* data = (float*)calloc(size,sizeof(float));

    float buffer = 0.0;

    //compute matrix multiplication between weights' matrix and input vector
    //then add bias to result's vector
    for(int i=0;i<size;i++){

        for(int y=0;y<inputSize;y++){

            //use buffer to store steps of multication
            buffer += input[y]*weights[i+(y*size)];
            
        }

        //add bias to mutiplication's result
        buffer+=bias[i];

        //pass result to sigmoid function that acts as activiation function (not exactly but shhhhh)
        buffer = (1/(1+exp(buffer)));

        //write rectified buffer's value to data
        data[i] = buffer;
        buffer = 0.0;
    }

    free(input);

    return data;

}

void layer::mergeLayer(layer* layer1,layer* layer2,float randomRate){

    layer::size = layer1->size;
    layer::inputSize = layer1->inputSize;

    layer::weights = (float*)calloc(inputSize*size,sizeof(float));
    layer::bias = (float*)calloc(size,sizeof(float));

    for(int i = 0; i< inputSize*size;i++){
        
        layer::weights[i] = rand() % 1000 <= randomRate*1000?
         (static_cast<float>( rand()) / static_cast<float>(RAND_MAX))*2-1:
        rand() <= rand()? layer1->weights[i]:layer2->weights[i];

    }

    for(int i = 0; i< size;i++){
        
        layer::bias[i] = rand() % 1000 <= randomRate*1000?
         (static_cast<float>( rand()) / static_cast<float>(RAND_MAX))*2-1:
        rand() <= rand()? layer1->bias[i]:layer2->bias[i];

    }

}
