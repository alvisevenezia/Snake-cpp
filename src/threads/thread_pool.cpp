#include "thread_pool.h"
#include <vector>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <utility>

thread_pool::thread_pool(int thread_quantity){

    thread_pool::thread_quantity = thread_quantity;
}

int thread_pool::start_pool(){

    threads.resize(thread_quantity);
    for(int id = 0;id < thread_quantity;id++){

        threads.at(id) = std::thread(&thread_pool::worker_loop,this);
    }

    return 0;

}

void thread_pool::worker_loop() {

    std::cout<<std::this_thread::get_id()<<std::endl;

    while (true) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, [this] {
                return !jobs.empty() || should_terminate;
            });
            if (should_terminate) {
                return;
            }
            if(!jobs.empty()){

                job = jobs.front(); 
                jobs.pop();
                job();
            }

            
        }

        
    }
}

bool thread_pool::pool_busy(){

    return !jobs.empty();

}

int thread_pool::stop_pool(){

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (std::thread& active_thread : threads) {
        active_thread.join();
    }
    threads.clear();

    return 0;

}