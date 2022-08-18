class snake
{
private:
   
    struct snakePart{
        snakePart* next;
        snakePart* previous;
        int id,x,y;
    };
    
    

public:

    struct snakePart * head;
    struct snakePart * tail;

    bool dead,nml;
    float* map;
    int mapSize,apple,moves,step,bonusMoves,fieldOfVue;
    int last_x_move,last_y_move;
    unsigned long long fitness;

    ~snake();

    /**
     * @brief move snake 
     * 
     * @param x x movement of the snake
     * @param y y movement of the snake
     * @return true snake is alive 
     * @return false snake died when moving
     */
    bool updateParts(float r,float s,float l);

    /**
     * @brief initialize snake
     * 
     * @param mapSize size of the map
     * @param x x value for the head
     * @param y y value for the head
     */
    void initSnake(int* mapSize,int x,int y);

    /**
     * @brief spawn random apple
     * 
     */
    void spawnApple();

    float* generateInput_data();

    float getFoodDistance(int x_direction,int y_direction);

    float getBorderDistance(int x_direction,int y_direction);

    float getSelfDistance(int x_direction,int y_direction);

};

