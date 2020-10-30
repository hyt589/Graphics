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
#define HYT_ASSERT(condition, ...)                   \
    if (!condition)                                  \
    {                                                \
        LOG_ERROR("[ASSERT_FAIL] {0}", __VA_ARGS__); \
        HYT_DEBUG_BREAK;                             \
    }
#else
#define HYT_ASSERT(condition, ...)
#endif // !NDEBUG

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
//define something for Windows (32-bit and 64-bit, this part is common)
#define HYT_PLATFORM_WIN
#ifdef _WIN64
#define HYT_PLATFORM_WIN64
//define something for Windows (64-bit only)
#else
#define HYT_PLATFORM_WIN32
//define something for Windows (32-bit only)
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#define HYT_PLATFORM_MAC_OS
#else
#error "Unknown Apple platform"
#endif
#elif __linux__
// linux
#define HYT_PLATFORM_LINUX
#elif __unix__ // all unices not caught above
// Unix
#define HYT_PLATFORM_UNIX

#elif defined(_POSIX_VERSION)
// POSIX
#define HYT_PLATFORM_POSIX
#else
#error "Unknown compiler"
#endif

namespace HYT
{
    enum GraphicsAPI
    {
        none,
        opengl,
        vulkan,
        dx11,
        dx12,
        metal
    };

    enum WindowAPI
    {
        None,
        GLFW,
        WIN32
    };

} // namespace HYT
