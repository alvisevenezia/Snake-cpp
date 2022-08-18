#include "network.h"
#include <iostream>

network::~network(){

    for(int id  = 0; id<networkSize;id++){
        delete layerArray[id];
    }

    free(Snake->map);
    delete Snake;

    free(layerArray);
}

void network::initNetwork(int* mapSize,int networkSize,int* layerSize,int id){

    //set network's internal variables
    network::layerSize = layerSize;
    network::networkSize = networkSize;
    network::id = id;
    network::layerArray = (layer**)malloc(networkSize*sizeof(layer*));

    //initialize each layer according to layer size
    for(int i = 0;i<networkSize;i++){

        //creates and init a layer
        layer* Layer = new layer;
        Layer->initLayer(layerSize[i],(i == 0 ?24:layerSize[i-1]));
        network::layerArray[i] = Layer;
    }

    //initialize snake
    network::Snake = new snake();
    network::Snake->initSnake(mapSize,(*mapSize/2)+1,(*mapSize/2)+1);
}



bool network::compute(){

    //compute for first layer using map as input values
    float* data = layerArray[0]->compute(Snake->generateInput_data(),0);

    //loop for each other layer using previous layer's result as input
    for(int i = 1;i<networkSize;i++){
    
        data = layerArray[i]->compute(data,i);

    }

    //send last layer data to update the snakes
    bool check = network::Snake->updateParts(data[0],data[1],data[2]);
    free(data);

    return check;

}

void network::mergeNetwork(network* parent1,network* parent2,float randomRate){

    //initiate value of new network with parent14S one
    network::layerSize = parent1->layerSize;
    network::networkSize = parent1->networkSize;

    //create the layer array
    network::layerArray = (layer**)malloc(networkSize*sizeof(layer*));

    //create each layer
    for(int id = 0; id<networkSize; id++){
        
        //create layer
        layer* Layer = new layer();  

        //merge parents' layer into it 
        Layer->mergeLayer(parent1->layerArray[id],parent2->layerArray[id],randomRate);
        
        //put the layer in the array
        network::layerArray[id] = Layer;
    }

    //create a snake for the network
    network::Snake = new snake();

    //initiate the snake
    network::Snake->initSnake(&(parent1->Snake->mapSize),(parent1->Snake->mapSize/2)+1,(parent1->Snake->mapSize/2)+1);   

}
