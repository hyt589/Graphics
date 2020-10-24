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
        //MacOS only support OpenGL up to 4.1
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        m_nativeWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), NULL, NULL);

        glfwMakeContextCurrent(m_nativeWindow);
        GL(int gl_load_status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
        if(!gl_load_status)
        {
            LOG_CRITICAL("[OpenGL] Glad initialization failed");
            std::raise(SIGINT);
        }

        glfwSetWindowUserPointer(m_nativeWindow, this);

        glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow * window){
            auto * ptr = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
            ptr->post(Event(EventType::WindowCloseEvent));
        });

        LOG_INFO("OpenGL Info:");
		LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void GlfwWindow::post(Event e)
    {
        m_eventDispatcher.post(e, APP_EVENT_QUEUE);
    }

    void GlfwWindow::onUpdate()
    {
        glfwSwapBuffers(m_nativeWindow);
        glfwPollEvents();
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
