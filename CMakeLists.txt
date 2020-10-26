cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Engine VERSION 0.1.0)

include(CTest)
enable_testing()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/glfw)

set(LIB spdlog::spdlog glfw)

file(GLOB CORE_SOURCE_FILES
    dependencies/glad/src/glad.c
    src/Core/**.cpp
    src/ImGui/**.cpp
    dependencies/imgui/*.cpp
)

file(GLOB OGL_SRC
    src/OpenGL/*.cpp
    src/Apps/AppOpenGL/*.cpp
    dependencies/imgui/backends/imgui_impl_opengl3.cpp
)

include_directories(
    src/App
    src/Core
    src/ImGui
    src/OpenGL
    src/Apps/AppOpenGL
    dependencies/glad/include
    dependencies/glm/glm
    dependencies/spdlog/include
    dependencies/magic_enum/include
    dependencies/imgui
)

set_source_files_properties(dependencies/glad/src/glad.c PROPERTIES SKIP_PRECOMPILE_HEADERS on)

add_executable(Application_OpenGL ${CORE_SOURCE_FILES} ${OGL_SRC})

# target_precompile_headers(
#     Application
#     PUBLIC
#     src/Core/global.hpp
# )
target_link_libraries(Application_OpenGL PRIVATE ${LIB})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
