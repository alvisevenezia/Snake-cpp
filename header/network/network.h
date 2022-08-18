#include "layer.h"
#include "snake.h"

class network{

    public:

        layer** layerArray;
        int* layerSize;   
        int networkSize,id,apple;
        snake* Snake; 

    ~network();

    /**
     * @brief initialize network
     * 
     * @param networkSize size of the network
     * @param layerSize size of each layer 
     * @param id id of network
     */
    void initNetwork(int* mapSize,int networkSize,int* layerSize,int id);

    /**
     * @brief create a new network based on two parents
     * 
     * @param parent1 1st parent
     * @param parent2 2nd parent
     */
    void mergeNetwork(network* parent1,network* parent2,float mergingRate);

    /**
     * @brief starts computation of the network
     * 
     */
    bool compute();
};