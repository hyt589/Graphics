#include "Timer.hpp"

namespace HYT::Timer
{
    std::chrono::time_point<std::chrono::steady_clock> now()
    {
        return std::chrono::steady_clock::now();
    }

    long long ellapsedMilliseconds(std::chrono::time_point<std::chrono::steady_clock> & start, std::chrono::time_point<std::chrono::steady_clock> & end)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }


    double ellapsedSeconds(std::chrono::time_point<std::chrono::steady_clock> & start, std::chrono::time_point<std::chrono::steady_clock> & end)
    {
        return (float)ellapsedMilliseconds(start, end) / 1000.0;
    }
} // namespace HYT::Timer
