#include "GlfwWindow.hpp"

namespace HYT
{
    Window *Window::Create(const WindowProps &props)
    {
        return new OpenGL::GlfwWindow(props);
    }
} // namespace HYT

namespace HYT::OpenGL
{
    GlfwWindow::GlfwWindow(const WindowProps &props)
    {
        glfwInit();
        m_nativeWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), NULL, NULL);

        glfwMakeContextCurrent(m_nativeWindow);
        GL(int gl_load_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
        if(!gl_load_status)
        {
            LOG_ERROR("[OpenGL] Glad initialization failed");
            std::raise(SIGINT);
        }

        LOG_INFO("OpenGL Info:");
		LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void GlfwWindow::onUpdate()
    {

    }

    void GlfwWindow::getSize(int & w, int & h)
    {
        glfwGetWindowSize(m_nativeWindow, &w, &h);
    }

    void * GlfwWindow::GetNativeWindow() const
    {
        return m_nativeWindow;
    }


} // namespace HYT::OpenGL
