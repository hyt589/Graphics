#include "Timer.hpp"

namespace HYT::Timer
{
    std::chrono::time_point<std::chrono::steady_clock> now()
    {
        return std::chrono::steady_clock::now();
    }

    double ellapsedMilliseconds(std::chrono::time_point<std::chrono::steady_clock> & start, std::chrono::time_point<std::chrono::steady_clock> & end)
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    double ellapsedSeconds(std::chrono::time_point<std::chrono::steady_clock> & start, std::chrono::time_point<std::chrono::steady_clock> & end)
    {
        return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    }
} // namespace HYT::Timer
