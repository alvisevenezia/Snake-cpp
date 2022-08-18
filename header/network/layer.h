class layer{

    private:

        float* weights;
        float* bias;
        

    public:
        int size,inputSize;
    
    ~layer();    

    /**
     * @brief initialize weights and bias of layer
     * 
     * @param size size of layer (quantity of neuron)
     * @param inputSize size of input data (quantity of weight for each neuron)
     */
    void initLayer(int size,int inputSize);

    /**
     * @brief compute this layer with input data
     * 
     * @param input input data (map if 1st layer, result of previous layer's computation else)
     * @return int* result of computation
     */
    float* compute(float* input,int id);

    void mergeLayer(layer* layer1,layer* layer2,float mergingRate);

};