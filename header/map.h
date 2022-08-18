#include <thread>

class map{

    private:

        struct node
        {
            std::thread::id key;
            bool value;
            node* next;

        };

        node* begin;
        

    public:

    map();

    ~map();

    int add(std::thread::id key,bool value);

    int remove(std::thread::id key);

    bool operator[](std::thread::id key);

};