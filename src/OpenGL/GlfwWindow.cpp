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
        if (!gl_load_status)
        {
            LOG_CRITICAL("[OpenGL] Glad initialization failed");
            std::raise(SIGINT);
        }

        glfwSetWindowUserPointer(m_nativeWindow, this);

        glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow *window) {
            auto *windowPtr = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            windowPtr->post(Event(EventType::WindowCloseEvent));
        });

        glfwSetFramebufferSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height){
            auto windowPtr = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            glm::vec2 size(width, height);
            windowPtr->post(Event(EventType::WindowResizeEvent, size));
        });

        glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            auto windowPtr = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
            {
                windowPtr->post(Event(EventType::KeyPressEvent, key));
                break;
            }
            case GLFW_RELEASE:
            {
                windowPtr->post(Event(EventType::KeyReleaseEvent, key));
                break;
            }
            case GLFW_REPEAT:
            {
                windowPtr->post(Event(EventType::KeyRepeatEvent, key));
                break;
            }
            default:
                break;
            }
        });

        glfwSetMouseButtonCallback(m_nativeWindow, [](GLFWwindow *window, int button, int action, int mods) {
            auto windowPtr = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS:
            {
                windowPtr->post(Event(EventType::MouseButtonPressEvent, button));
                break;
            }
            case GLFW_RELEASE:
            {
                windowPtr->post(Event(EventType::MouseButtonReleaseEvent, button));
                break;
            }
            case GLFW_REPEAT:
            {
                windowPtr->post(Event(EventType::MouseButtonRepeatEvent, button));
                break;
            }
            default:
                break;
            }
        });

        glfwSetCursorPosCallback(m_nativeWindow, [](GLFWwindow* window, double xpos, double ypos)
        {
            auto windowPtr = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            glm::vec2 xy(xpos, ypos);
            windowPtr->post(Event(EventType::CursorPosEvent, xy));
        });

        glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xoffset, double yoffset){
            auto windowPtr = static_cast<GlfwWindow *>(glfwGetWindowUserPointer(window));
            glm::vec2 xy(xoffset, yoffset);
            windowPtr->post(Event(EventType::ScrollEvent, xy));
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

    void GlfwWindow::getSize(int &w, int &h)
    {
        glfwGetWindowSize(m_nativeWindow, &w, &h);
    }

    void *GlfwWindow::GetNativeWindow() const
    {
        return m_nativeWindow;
    }

} // namespace HYT::OpenGL
