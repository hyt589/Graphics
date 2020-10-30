/**
 * @file global.hpp
 * @author Yutong Huang (yutong.huang@outlook.com)
 * @brief Include all necessary headers from STL
 * @version 0.1
 * @date 2020-10-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#pragma once

#include <iostream>
#include <functional>
#include <algorithm>
#include <memory>
#include <chrono>
#include <fstream>
#include <sstream>
#include <csignal>
#include <initializer_list>

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <any>

#include <thread>
#include <future>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define HYT_DEBUG_BREAK std::raise(SIGINT) 


#ifndef NDEBUG
#define HYT_ASSERT(condition, ...) if (!condition){LOG_ERROR("[ASSERT] {0}", __VA_ARGS__);HYT_DEBUG_BREAK;}
#else
#define HYT_ASSERT(condition, ...)
#endif // !NDEBUG

namespace HYT
{
    enum GraphicsAPI
    {
        none,
        opengl,
        #ifndef __APPLE__
        vulkan,
        #endif // !__APPLE__
        #ifdef __WIN32__
        dx11,
        dx12,
        #endif // __WIN32__
        #ifdef __APPLE__
        metal
        #endif // __APPLE__
    };

    enum WindowAPI
    {
        GLFW
    };

    inline GraphicsAPI g_render_api = GraphicsAPI::opengl;
    inline WindowAPI g_window_api = WindowAPI::GLFW;

} // namespace HYT
