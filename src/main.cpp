#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include "game/game.h"
#include "thread_pool.h"

#define DEBUG

void work_function(int id){

    std::cout<<id<<std::endl;

}

void test_thread_pool(){

    thread_pool pool(20);
    pool.start_pool();

    for(int id = 0;id <1000000;id++){

        pool.queue_work(work_function,id);
    }

    while (pool.pool_busy())
    {
    }
    
    pool.stop_pool();

}

int main(int argc, char const *argv[])
{

    bool randomSet = false;
    int threadcount = 1;
    int popQuantity = 200;
    int newSnakeQuantity = 20;
    int randomRate = 5;
    int parentQuantity = 20;
    int mapSize = 15;
    int seed = time(NULL);
    
    //checks for args
    if(argc > 1){

        while(argc > 1){

            if(strcmp(argv[argc-1],"-threadcount") == 0 || strcmp(argv[argc-1],"-tc") == 0){
                
                if((threadcount = atoi(argv[argc])) > 0){

                    if(threadcount > (signed)std::thread::hardware_concurrency()){
                        
                        threadcount = std::thread::hardware_concurrency();
                        std::cout<<"specified argument greater than hardware possibilities, treadcount set to "<<threadcount<<std::endl;

                    }

                }else{

                    std::cout<<"-threadcount should be greater than 0"<<std::endl;
                    exit(1);
                }

            }if(strcmp(argv[argc-1],"-rs") == 0 || strcmp(argv[argc-1],"-randomSeed") == 0){

                std::cout<<"randomSeed set to "<<argv[argc]<<std::endl;
                seed = atoi(argv[argc]);
                randomSet = true;
            }if(strcmp(argv[argc-1],"-pq") == 0 || strcmp(argv[argc-1],"-popQuantity") == 0){

                
                popQuantity = atoi(argv[argc]);

            }if(strcmp(argv[argc-1],"-rr") == 0 || strcmp(argv[argc-1],"-randomrate") == 0){

                
                randomRate = (float)atoi(argv[argc]);

                if(randomRate < 0){

                     std::cout<<"randomRate should be greater or equal than 0"<<std::endl;

                }

                
            }if(strcmp(argv[argc-1],"-ns") == 0 || strcmp(argv[argc-1],"-newsnakequantity") == 0){


                if(newSnakeQuantity < 0){

                     std::cout<<"newSnakeQuantity should be greater of equal than 0"<<std::endl;

                }else{
                    newSnakeQuantity = atoi(argv[argc]);
                }
            }if(strcmp(argv[argc-1],"-paq") == 0 || strcmp(argv[argc-1],"-parentquantity") == 0){
                

                if(parentQuantity <= 0){

                     std::cout<<"parentQuantity should be greater  than 0"<<std::endl;

                }else{
                    parentQuantity = atoi(argv[argc]);
                }
            }if(strcmp(argv[argc-1],"-ms") == 0 || strcmp(argv[argc-1],"-mapsize") == 0){
                

                if(mapSize <= 5){

                     std::cout<<"mapSize should be greater 5"<<std::endl;

                }else{
                    mapSize = atoi(argv[argc]);
                }
            }

        argc--;

        }

    }
    if(!randomSet){

    std::cout<<"randomSeed set to random ("<<seed<<")"<<std::endl;

    }

    if(popQuantity < parentQuantity){

        std::cout<<"popQuantity should be greater than "<<parentQuantity<<std::endl;
        popQuantity = parentQuantity+1;

    }

    std::cout<<"popQuantity set to "<<popQuantity<<std::endl;
    std::cout<<"parentQuantity set to "<<parentQuantity<<std::endl;
    std::cout<<"randomRate set to "<<(float)randomRate/1000<<std::endl;
    std::cout<<"newSnakeQuantity set to "<<newSnakeQuantity<<std::endl;
    std::cout<<"mapSize set to "<<mapSize<<std::endl;

    srand(seed);

    //init game
    game Game;
    int layerSize[] = {18,18,3};

    #ifdef DEBUG

    mkdir("results",0777);
    mkdir("results/0",0777);

    #endif

    mkdir("stats",0755);

    Game.initGame(popQuantity,mapSize,0,3,layerSize,threadcount,((float)randomRate)/1000,newSnakeQuantity,parentQuantity);
    Game.startGame();
    std::cout<<"DONE"<<std::endl;
    return 0;
}
