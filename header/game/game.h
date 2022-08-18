#include "network.h"
#include <iostream>
#include <thread>

class game
{
private:
    
    int threadQuantity;
    
public:
    float randomRate;
    network** networkArray;
    bool* threadState,gameState;
    int mapSize,genID,popQuantity,parentQuantity,newSnakeQuantity;
    int* deadCountArray;

    /**
     * @brief intialize the game object
     * 
     * @param popQuantity quantity of snake for each generation
     * @param mapSize size of the map on which snakes play
     * @param genID id of the first generation. Not 0 if loading already trained snakes
     * @param layerSize size of layers
     * @param threadQuantity available quantity of thread
     * @param randomRate rate of random neuronn added in merging
     * @param newSnakeQuantity quantity of new snake added each generation
     * @param parentQuantity size of snake's pool used to create new generation
     */
    void initGame(int popQuantity,int mapSize,int genID,int networkSize,int* layerSize,int threadQuantity,float randomRate,int newSnakeQuantity,int parentQuantity);

    /**
     * @brief function du merge snake and create next gen
     * 
     */

    void mergeSnakes();

    /**
     * @brief start the game routine
     * 
     */
    void startGame();

    /**
     * @brief pause the game routine
     * 
     * 
     */
    void pauseGame();
    
    /**
     * @brief stop the game
     * 
     */
    void stopGame();

    /**
     * @brief function to check if all thread are done
     * 
     * @return TRUE if threads are running
     * @return FALSE if all threads are waiting
     */
    bool checkState();

    bool computeNetwork(int id);
    
};