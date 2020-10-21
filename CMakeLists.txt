cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Application VERSION 0.1.0)

include(CTest)
enable_testing()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/glfw)

set(LIB spdlog::spdlog glfw)

file(GLOB SOURCE_FILES
    dependencies/glad/src/glad.c
    src/**/*.cpp
)

include_directories(
    src/App
    src/Core
    dependencies/glad/include
)

set_source_files_properties(dependencies/glad/src/glad.c PROPERTIES SKIP_PRECOMPILE_HEADERS on)

add_executable(Application ${SOURCE_FILES})

target_precompile_headers(
    Application
    PUBLIC
    src/Core/global.hpp
)
target_link_libraries(Application PRIVATE ${LIB})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
