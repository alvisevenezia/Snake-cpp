#include <vector>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <map.h>
#include <future>


class thread_pool{

    public:

    bool should_terminate = false;          
    std::mutex queue_mutex;                  
    std::condition_variable mutex_condition;
    std::queue<std::function<void()>> jobs;
    std::vector<std::thread> threads;

    int thread_quantity;

    thread_pool(int thread_quantity);
    
    int start_pool();

    //from https://github.com/mtrebi/thread-pool
    template<typename F, typename...Args>
    auto queue_work(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        // Create a function with bounded parameters ready to execute
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        // Encapsulate it into a shared ptr in order to be able to copy construct / assign 
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        // Wrap packaged task into void function
        std::function<void()> wrapper_func = [task_ptr]() {
        (*task_ptr)(); 
        };

        // Enqueue generic wrapper function
        jobs.push(wrapper_func);

        // Wake up one thread if its waiting
        mutex_condition.notify_one();

        // Return future from promise
        return task_ptr->get_future();
    }
    

    int stop_pool();

    bool pool_busy();

    void worker_loop();

};