#pragma once

#include "global.hpp"

/**
 * @brief Functions related to time
 * 
 */
namespace HYT::Timer
{
    std::chrono::time_point<std::chrono::steady_clock> now();

    long long ellapsedMilliseconds(std::chrono::time_point<std::chrono::steady_clock> & start, std::chrono::time_point<std::chrono::steady_clock> & end);
    double ellapsedSeconds(std::chrono::time_point<std::chrono::steady_clock> & start, std::chrono::time_point<std::chrono::steady_clock> & end);
} // namespace HYT
