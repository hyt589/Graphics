cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
project(Application VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB SOURCE_FILES
    src/App/EntryPoint.cpp
    src/Core/Event.cpp
)

include_directories(
    src/App
    src/Core
)

add_executable(Application ${SOURCE_FILES})

target_precompile_headers(
    Application
    PUBLIC
    src/Core/global.hpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
