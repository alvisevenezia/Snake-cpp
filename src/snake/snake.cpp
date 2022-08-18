#include "snake.h"
#include <cmath>
#include <stdlib.h>
#include <iostream>

//snake destructor
snake::~snake(){

    //destroy each snakePart
    while(head->next !=nullptr){

        //go to the next part and then free the previous one
        head = head->next;
        free(head->previous);

    }
    
    //free the head wich isn't freed before
    free(head);

}

void snake::initSnake(int* mapSize,int x,int y){

    //initialize map full of zero
    snake::map = (float*)calloc(*mapSize**mapSize,sizeof(float));
    snake::mapSize = *mapSize;
    snake::last_x_move = 0;
    snake::last_y_move = (rand()%2)==0?-1:1;
    //set head to (x,y)
    snake::map[(x)+(y*snake::mapSize)] = 1.0;

    snake::fitness = 0;
    snake::moves = *mapSize*2.5;;
    snake::apple = 0;
    snake::dead = false;
    snake::step = 0;
    snake::nml = false;
    snake::bonusMoves = *mapSize*2.5;
    snake::fieldOfVue = *mapSize/2;

    //create snakePart for head and tail
    snake::head = (snakePart*)malloc(sizeof(snakePart));
    snake::head->next = nullptr;
    snake::head->previous = nullptr;
    snake::head->id = 1;
    snake::head->x = x;
    snake::head->y = y;

    snake::tail = head; //set tail as nullptr cause we do not have tail for now

} 

bool snake::updateParts(float right_neuronn,float stay_neuronn,float left_neuronn){

    //buffer value for x and y 
    int x = 0;
    int y = 0;

    //set x and y depending on the last move 
    if(stay_neuronn > left_neuronn && stay_neuronn > right_neuronn){

        //if the network decides to stay wiht the same mouvement, do not change the mouvement
        x = last_x_move;
        y = last_y_move;
        
    }else if(left_neuronn>stay_neuronn && left_neuronn> right_neuronn){

        //if the network decides to turn left, change x and y
        //if last move was up, go left
        //if last move was left, go down
        //if last move was down, go right
        //if last move was right, go up

        if(last_x_move > 0 && last_y_move == 0){
            x = 0;
            y = -1;
        }else if(last_x_move < 0 && last_y_move == 0){
            x = 0;
            y = 1;
        }else if(last_x_move == 0 && last_y_move < 0){
            x = -1;
            y = 0;
        }else if(last_x_move == 0 && last_y_move > 0){
            x = 1;
            y = 0;
        }
        
    }else{

        //if the network decides to turn right, change x and y
        //if last move was up, go right
        //if last move was left, go up
        //if last move was down, go left
        //if last move was right, go down

        if(last_x_move > 0 && last_y_move == 0){
            x = 0;
            y = 1;
        }else if(last_x_move < 0 && last_y_move == 0){
            x = 0;
            y = -1;
        }else if(last_x_move == 0 && last_y_move < 0){
            x = 1;
            y = 0;
        }else if(last_x_move == 0 && last_y_move > 0){
            x = -1;
            y = 0;
        }

    }
    
    //keep track of the current choosen movement for the next step
    last_x_move = x;
    last_y_move = y;

    //boolean if we should grow the snake
    bool grow = false;

    //new coordinate of head
    int nx = snake::head->x + x;
    int ny = snake::head->y + y;

    //decrement the number of snake's remaining mouvement
    moves--;

    //check if snake stays in map
    if(ny >=0 && ny < snake::mapSize && nx >= 0 && nx < snake::mapSize){

        //check if the snake eats itself and don't move on its tail (it will be moved later so that the case is free)
        if(snake::map[nx+(ny*snake::mapSize)] > 0 && snake::tail->x != nx && snake::tail->y != ny){

            //set the snake as dead and return false
            dead = true;
            return false;
        }

        //checks if snake eats an apple
        if(snake::map[nx+(ny*snake::mapSize)] == -1){
            
            // apple count 
            apple++;

            //increment remaining mouvement by <bonusMoves> 
            moves += bonusMoves;

            //set grow variable to true (used later to grow the snake)
            grow = true;
        }

        //create a buffer snakePart pointing to the head
        snakePart* pointer = snake::head;

        //keep track of the new position and the new id of the snakePart <pointer> is pointing to
        int lx = nx;
        int ly = ny;
        int lid = 0;

        //update id of all parts
        while(pointer != NULL){

            //set the old position of the snakepart to 0
            snake::map[pointer->x+(pointer->y*snake::mapSize)] = 0;

            //set the new position of the snakepart to the correct id
            snake::map[lx+(ly*snake::mapSize)] = pointer->id;

            //store the current x and y coordinate of the pointer
            int currentx = pointer->x;
            int currenty = pointer->y;

            //move the snakePart pointer is pointing to
            pointer->x = lx;
            pointer->y = ly;

            //keep the last x,y and id value to use it for the nex snakePart
            lx = currentx;
            ly = currenty;
            lid = pointer->id;

            //point to the next snakePArt
            pointer = pointer->next;         
            
        }

        //if snake schould grow
        if(grow){

            //create a new tail an link it to the old one
            snakePart* newtail = (snakePart*)malloc(sizeof(snakePart));
            newtail->previous = pointer;
            newtail->next = nullptr;
            tail->next = newtail;

            //set the new tail coordinate
            newtail->id = lid+1;
            newtail->x = lx;
            newtail->y = ly;

            //set the new tail as the actual tail
            tail = newtail;

            //place the new tail on the map
            snake::map[lx+(ly*snake::mapSize)] = newtail->id;

        }

        //if apple has been eat, spawn a new one 
        if(grow)spawnApple();

        //if snake has no move available, kill it
        if(moves <= 0){
            
            //set nml value to true (used to keep track of snake's dead)
            nml = true;

            //set snake as dead and return false
            dead = true;
            return false;
        }

    }else{

        //if snake moved out of the map
        //set snake as dead and return false
        dead = true;
        return false;
    } 
    
    //increment step counter by 1
    step++;

    //compute fitness
    if(apple < 10){
        
        //fitness = step^2*2^apple
        fitness = floor(step*step) * pow(2,apple);

    }else{
        
        //fitness = step^2*2^apple*(apple-9)
        fitness = floor(step*step) * pow(2,10);
        fitness*= apple-9;
    }
 

    return true;

}

void snake::spawnApple(){

    //generate random value for x and y 
    int x = rand() % mapSize;
    int y = rand() % mapSize;

    if(map[x+(y*mapSize)] != 0 || head->x == x || head->y == y){
        return spawnApple();
    }

    //spawn apple on map
    map[x+(y*mapSize)] = -1;
}

float* snake::generateInput_data(){

    float* data = (float*)malloc(24*sizeof(float));

    int x_direction = 0;
    int y_direction = 0;
    int offset = 0;

    if(last_y_move < 0)offset = 0;
    else if(last_y_move > 0)offset = 4;
    else if(last_x_move < 0)offset = 6;
    else if(last_x_move > 0)offset = 2;

    int id = 0;

    for(;id<8;id++){

        switch (id)
        {
        case 0:
            x_direction = -1;
            y_direction = -1;  
            break;
        case 1:
            x_direction = 0;
            y_direction = -1;  
            break;    
        case 2:
            x_direction = 1;
            y_direction = 1;  
            break;
        case 3:
            x_direction = 0;
            y_direction = 1;  
            break;   
        case 4:
            x_direction = 1;
            y_direction = 1;
            break;
        case 5:
            x_direction = 0;
            y_direction = 1;     
            break;
        case 6:
            x_direction = -1;
            y_direction = 1;  
            break; 
        case 8:
            x_direction = -1;
            y_direction = 0;
            break;

        default:
            break;
        }

        data[((id+offset)%8)*3] = getFoodDistance(x_direction,y_direction);
        data[((id+offset)%8)*3 +1] = getBorderDistance(x_direction,y_direction);
        data[((id+offset)%8)*3 +2] = getSelfDistance(x_direction,y_direction);
        
        switch (id)
        {
        case 0:
            /* code */
            break;
        
        default:
            break;
        }

    }
    
    return data;

}

float snake::getFoodDistance(int x_direction,int y_direction){

    int lastpos_x = snake::head->x;
    int lastpos_y = snake::head->y;
    float distance = 0;

    for(int i = 0;i<mapSize && i <fieldOfVue;i++){

        lastpos_x+= x_direction;
        lastpos_y+= y_direction;
        if(lastpos_x < 0 || lastpos_y < 0 || lastpos_x >= mapSize || lastpos_y >= mapSize)break;
        if(snake::map[lastpos_x+mapSize*lastpos_y] == -1)
        distance = 1/hypot(snake::head->x - lastpos_x,snake::head->y - lastpos_y);

    }

    return distance;

}

float snake::getBorderDistance(int x_direction,int y_direction){

    int lastpos_x = snake::head->x;
    int lastpos_y = snake::head->y;
    float distance = 0;

    for(int i = 0;i<mapSize && i <fieldOfVue;i++){

        lastpos_x+= x_direction;
        lastpos_y+= y_direction;
        if(lastpos_x < 0 || lastpos_y < 0 || lastpos_x >= mapSize || lastpos_y >= mapSize)
        return 1/hypot(snake::head->x - lastpos_x,snake::head->y - lastpos_y);

    }

    return distance;

}

float snake::getSelfDistance(int x_direction,int y_direction){

    int lastpos_x = snake::head->x;
    int lastpos_y = snake::head->y;
    float distance = 0;

    for(int i = 0;i<mapSize && i <fieldOfVue;i++){

        lastpos_x+= x_direction;
        lastpos_y+= y_direction;
        if(lastpos_x < 0 || lastpos_y < 0 || lastpos_x >= mapSize || lastpos_y >= mapSize)break;
        if(snake::map[lastpos_x+mapSize*lastpos_y] > 0)
        distance = 1/hypot(snake::head->x - lastpos_x,snake::head->y - lastpos_y);
        

    }

    return distance;

}