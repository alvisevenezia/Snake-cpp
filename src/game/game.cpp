#include "game.h"
#include "csv_utils.h"
#include "sys/stat.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <assert.h>
#include <fstream>
#include <stdio.h>
#include "thread_pool.h"

void game::initGame(int popQuantity,int mapSize,int genID,int networkSize,int* layerSize,int threadQuantity,float randomRate,int newSnakeQuantity,int parentQuantity){

    //initialize all value 
    game::popQuantity = popQuantity;
    game::mapSize = mapSize;
    game::genID = genID;
    game::threadQuantity = threadQuantity;
    game::randomRate = randomRate;
    game::newSnakeQuantity = newSnakeQuantity;
    game::gameState = false;
    game::networkArray = (network**)malloc(popQuantity*sizeof(network*));
    game::threadState = (bool*)malloc(threadQuantity*sizeof(bool));
    game::deadCountArray = (int*)malloc(threadQuantity*sizeof(int));
    game::parentQuantity = parentQuantity;

    //initialize networkArray
    network* Network;

    for(int i = 0; i< popQuantity;i++){

        //creates and init a network
        Network = new network();
        Network->initNetwork(&(game::mapSize),networkSize,layerSize,i);
        
        //puts it in networkArray
        game::networkArray[i] = Network;

    }

    //initialize threadStateArray;
    for(int i = 0; i< threadQuantity;i++){

        game::threadState[i] = false;

    }
}

/**
 * @brief function called by each thread
 * 
 * @param id id of thread
 */

void threadWork(game *game,int id){

    game->networkArray[id]->Snake->spawnApple();

    while(game->networkArray[id]->compute());

}


/**
 * @brief utilitarian function to sort networks' array

 */
void sortSnakes(network** inputArray,int popQuantity){

    //bubble sort
    network* buffer;
    bool swaped = true;

    while(swaped){
        
        swaped = false;

        for(int id = 0; id<popQuantity-1;id++){

            if(inputArray[id]->Snake->fitness < inputArray[id+1]->Snake->fitness){

                buffer = inputArray[id];
                inputArray[id] = inputArray[id+1];
                inputArray[id+1] = buffer;
                swaped = true;

            }
    
        }

    }

}


void game::mergeSnakes(){

    //sort the snake array
    sortSnakes(networkArray,popQuantity);
    
    //print best and worst fitness
    std::cout<<"best fitness: "<<networkArray[0]->Snake->fitness<<" ("<<genID<<":"<<networkArray[0]->id<<":"<<networkArray[0]->Snake->apple<<":"<<networkArray[0]->Snake->step<<":"<<networkArray[0]->Snake->nml<<")"<<std::endl;
    std::cout<<"worst fitness: "<<networkArray[popQuantity-1]->Snake->fitness<<std::endl;

    //write in a file the best snake stats
    FILE* stats_file = fopen("stats/stats.csv","a");
    fprintf(stats_file,"%d;%d;%d;%d;%llu;\n",genID,networkArray[0]->id,networkArray[0]->Snake->apple,networkArray[0]->Snake->step,networkArray[0]->Snake->fitness);
    fclose(stats_file);
    //write in a file a representation of the best snake 
    #ifdef BEST

        std::string path = 
        "results/"+std::to_string(genID)+
        "/"+std::to_string(networkArray[0]->id)+
        ".txt";
        writeCSVFile(
            path.c_str(),
            networkArray[0]->Snake->map,
            mapSize*mapSize,
            mapSize,
            0);

    #endif

    //free the unused network to get more memory space
    for(int id = parentQuantity;id<popQuantity;id++){
        delete networkArray[id];
    }

    //buffer value
    network* parent1;
    network* parent2;
    network* merged;

    //merge the networks according to merging parameters
    for(int id = parentQuantity+newSnakeQuantity; id< popQuantity; id++){

        //select two parent
        parent1 = networkArray[rand()%parentQuantity];
        parent2 = networkArray[rand()%parentQuantity];
    
        //create a newtwork to merge in
        merged = new network();

        //merge networks
        merged->mergeNetwork(parent1,parent2,randomRate);

        //set network's id
        merged->id = id;

        //place merged network in networkArray
        networkArray[id] = merged;
    }

    //keep the <parentQuantity> best network and reset their snake
    for(int id = 0;id < parentQuantity;id++){
        
        //delete old snake
        delete(networkArray[id]->Snake);

        //sets up network's new id
        networkArray[id]->id = id;

        //create a new snake
        networkArray[id]->Snake = new snake();

        //initialize the new snake
        networkArray[id]->Snake->initSnake(&mapSize,(mapSize/2)+1,(mapSize/2)+1);
    }

    //add new random snake according to <newSnakeQuantity>
    for(int id = parentQuantity;id < parentQuantity+newSnakeQuantity;id++){
        
        //create a new network
        networkArray[id] = new network();

        //initialize the new network
        networkArray[id]->initNetwork(&mapSize,networkArray[0]->networkSize,networkArray[0]->layerSize,id);    
    }

}

void mergeSnake(game *game,int id){

//buffer value
    network* parent1;
    network* parent2;
    network* merged;

    //merge the networks according to merging parameters
    if(id >= game->parentQuantity+game->newSnakeQuantity){

        //select two parent
        parent1 = game->networkArray[rand()%game->parentQuantity];
        parent2 = game->networkArray[rand()%game->parentQuantity];
    
        //create a newtwork to merge in
        merged = new network();

        //merge networks
        merged->mergeNetwork(parent1,parent2,game->randomRate);

        //set network's id
        merged->id = id;

        //place merged network in networkArray
        game->networkArray[id] = merged;

    }else if(id < game->parentQuantity){
        
        //delete old snake
        delete(game->networkArray[id]->Snake);

        //sets up network's new id
        game->networkArray[id]->id = id;

        //create a new snake
        game->networkArray[id]->Snake = new snake();

        //initialize the new snake
        game->networkArray[id]->Snake->initSnake(&game->mapSize,(game->mapSize/2)+1,(game->mapSize/2)+1);
    }else if(id >= game->parentQuantity && id <game->parentQuantity+game->newSnakeQuantity){
        
        //create a new network
        game->networkArray[id] = new network();

        //initialize the new network
        game->networkArray[id]->initNetwork(&game->mapSize,game->networkArray[0]->networkSize,game->networkArray[0]->layerSize,id);    
    }

}

//utilitarian function used to cleanly exit the programm to track memory leaks with valgrind
void freeEverything(game *game){

    //iterates on each network and delete it
    for(int id = 0; id < game->popQuantity;id++){

        //delete netowork (call network's destructor)
        delete(game->networkArray[id]);
        

    }

    //free the network's array
    free(game->networkArray);

}

void game::startGame(){

    //vector to store threads in usage (not used for now, may be usefull if a pool of thread is made later)
    std::vector<std::thread> threads;   
    threads.resize(20);


    //================ this part is done only for the first generation =======================

    //set game as running
    gameState = true;
    std::cout<<"threadCount: "<<threadQuantity<<std::endl;

    thread_pool pool(threadQuantity);
    pool.start_pool();

    while(true){

    for(int id =0;id <popQuantity;id++)pool.queue_work(&threadWork,this,id);
    
    while (pool.pool_busy());

    sortSnakes(networkArray,popQuantity);
    
    //print best and worst fitness
    std::cout<<"best fitness: "<<networkArray[0]->Snake->fitness<<" ("<<genID<<":"<<networkArray[0]->id<<":"<<networkArray[0]->Snake->apple<<":"<<networkArray[0]->Snake->step<<":"<<networkArray[0]->Snake->nml<<")"<<std::endl;
    std::cout<<"worst fitness: "<<networkArray[popQuantity-1]->Snake->fitness<<std::endl;
    
    //write in a file the best snake stats
    FILE* stats_file = fopen("stats/stats.csv","a");
    fprintf(stats_file,"%d;%d;%d;%d;%llu;\n",genID,networkArray[0]->id,networkArray[0]->Snake->apple,networkArray[0]->Snake->step,networkArray[0]->Snake->fitness);
    fclose(stats_file);
    //write in a file a representation of the best snake 
    #ifdef BEST

        std::string path = 
        "results/"+std::to_string(genID)+
        "/"+std::to_string(networkArray[0]->id)+
        ".txt";
        writeCSVFile(
            path.c_str(),
            networkArray[0]->Snake->map,
            mapSize*mapSize,
            mapSize,
            0);

    #endif

    genID++;

    //free the unused network to get more memory space
    for(int id = parentQuantity;id<popQuantity;id++){
        delete networkArray[id];
    }

    for(int id =0;id <popQuantity;id++)pool.queue_work(&mergeSnake,this,id);

    }

    while (pool.pool_busy());
    
    pool.stop_pool();

    //================ this part is done for each generation after the first one =======================

    //run until <?> is pressed TO DO
   /* while(true){

        //if all thread are waiting
        if(!checkState()){
            
            //merge snakes
            mergeSnakes();

            //increase genID
            genID++;

            //create a new folder to store snake's data

            #ifdef BEST

            std::string path = "results/"+std::to_string(game::genID);
            mkdir(path.c_str(),0777);

            #endif

            #ifdef DEBUG

            std::string path = "results/"+std::to_string(game::genID);
            mkdir(path.c_str(),0777);

            #endif
            
            //set all thread as running
            for(int id = 0;id < threadQuantity;id++)threadState[id] = true;

            //restart the game
            gameState = true;
        
        }
        

    }*/

 


}



bool game::checkState(){

    for(int id = 0;id < threadQuantity;id++){

        if(threadState[id] == true){
            
            gameState = true;
            return true;
        }
    }

    gameState = false;
    return false;

}