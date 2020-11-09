#include "ThreadPool.hpp"

namespace HYT
{
    ThreadPool::ThreadPool(int num_thread)
    {
        for (size_t i = 0; i < num_thread; i++)
        {
            m_pool.push_back(std::thread([this]() {
                while (true)
                {
                    Task task;
                    { //critical section
                        std::unique_lock<std::mutex> lock(m_mutex);
                        m_condition.wait(lock, [this] { return !m_tasks.empty() || m_shouldTerminate; });
                        if (m_shouldTerminate)
                        {
                            return;
                        }
                        task = m_tasks.front();
                        m_tasks.pop();
                    }
                    task();
                }
            }));
        }
    }
    ThreadPool::~ThreadPool()
    {
        if(!m_terminated)
        {
            terminate();
        }
    }

    void ThreadPool::pushTask(std::function<void()> task)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_tasks.push(task);
        }
        m_condition.notify_one();
    }

    void ThreadPool::terminate(std::function<bool()> condition, int milliseconds)
    {
        while (!condition())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
        };
        m_shouldTerminate = true;
        m_condition.notify_all();

        for (auto &thread : m_pool)
        {
            thread.join();
        }

        m_pool.clear();
        m_terminated = true;
    }

} // namespace HYT
