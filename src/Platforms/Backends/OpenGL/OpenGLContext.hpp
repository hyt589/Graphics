#pragma once

#include "Core.hpp"

//forward declaration
struct GLFWwindow;

namespace HYT::OpenGL
{
    class Context : public ::HYT::Render::Context
    {
    public:
        Context(GLFWwindow * window);
        virtual void init() override;
        virtual void swapBuffer() override;

    private:
        GLFWwindow * m_window;
    };
} // namespace HYT::OpenGL
