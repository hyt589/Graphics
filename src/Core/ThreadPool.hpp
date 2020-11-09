#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>

namespace HYT
{
    class ThreadPool
    {
    public:
        using Task = std::function<void()>;
        /**
         * @brief Construct a new Thread Pool object
         * 
         * @param num_thread Number of threads in the pool
         */
        ThreadPool(int num_thread = std::thread::hardware_concurrency());

        /**
         * @brief Destroy the Thread Pool object
         * 
         */
        ~ThreadPool();

        /**
         * @brief Push a task to the task queue
         * 
         * @param task the task to be performed. Should be a void function that takes no input
         */
        void pushTask(std::function<void()> task);
        
        /**
         * @brief Periodically checks the specified condition predicate and terminate the thread
         * pool when the condition is met.
         * 
         * @param condition a predicate that specifies the end condition
         * @param milliseconds the amount of time in milliseconds to wait before a condition check
         */
        void terminate(std::function<bool()> condition = []() { return true; }, int milliseconds = 100);

    private:
        std::vector<std::thread> m_pool;
        std::queue<Task> m_tasks;
        std::mutex m_mutex;
        bool m_shouldTerminate;
        bool m_terminated;
        std::condition_variable m_condition;
    };
} // namespace HYT
