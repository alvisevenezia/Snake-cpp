#include "map.h"

map::map(){

    begin = nullptr;

}

map::~map(){

    node* pointer = begin;

    while(pointer != nullptr){
        
        node* buffer = pointer;
        pointer = pointer->next;

        free(buffer);

    }

}

bool map::operator[](std::thread::id key){

    node* buffer = begin;

    while(buffer != nullptr){

        if(buffer->key == key)return buffer->value;

    }

    return NULL;

}

int map::add(std::thread::id key,bool value){

    node* buffer = new node;
    buffer->key = key;
    buffer->value = value;
    buffer->next = begin;

    begin = buffer;

}

int map::remove(std::thread::id key){

    node* pointer = begin;

    while(pointer->next != nullptr){

        if(pointer->next->key == key){

            node* buffer = pointer->next;
            pointer->next = pointer->next->next;

            free(buffer);
            return 0;
        }

        pointer = pointer->next;

    }

    if(begin->key == key){

        node* buffer = begin;
        begin = begin->next;

        free(buffer);
        return 0;

    }

    return 1;

}