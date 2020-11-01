#include "OpenGLContext.hpp"
#include "gl_base.hpp"
#include <GLFW/glfw3.h>



namespace HYT::OpenGL
{
    Context::Context(GLFWwindow *window)
        : m_window(window)
    {
        HYT_ASSERT((Window::getAPI() == WindowAPI::GLFW), "Cannot create OpenGL context in non GLFW windows");
        HYT_ASSERT(window, "No window for context creation");
        LOG_TRACE("[OpenGL] Context created");
    }

    void Context::init()
    {
        LOG_TRACE("[OpenGL] Context Initializing...");
        glfwMakeContextCurrent(m_window);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        HYT_ASSERT(status, "OpenGL context initialization failed: GLAD loading failed!")

        LOG_INFO("OpenGL Info:");
        LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void Context::swapBuffer()
    {
        LOG_TRACE("[OpenGL] Swaping buffer");
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
} // namespace HYT::OpenGL
