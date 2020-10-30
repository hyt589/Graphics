#include "MacGlfwWindow.hpp"

namespace HYT
{

    MacGlfwWindow::MacGlfwWindow(const WindowProps & props, int glVerMajor, int glVerMinor)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVerMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVerMinor);
        m_nativeWindow = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), NULL, NULL);
        

        glfwSetWindowUserPointer(m_nativeWindow, this);

        glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow *window) {
            auto *windowPtr = static_cast<MacGlfwWindow *>(glfwGetWindowUserPointer(window));
            windowPtr->post(Event(EventType::WindowCloseEvent));
        });

        glfwSetFramebufferSizeCallback(m_nativeWindow, [](GLFWwindow* window, int width, int height){
            auto windowPtr = static_cast<MacGlfwWindow *>(glfwGetWindowUserPointer(window));
            std::pair size(width, height);
            windowPtr->post(Event(EventType::WindowResizeEvent, size));
        });

        glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            auto windowPtr = static_cast<MacGlfwWindow *>(glfwGetWindowUserPointer(window));
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
            auto windowPtr = static_cast<MacGlfwWindow *>(glfwGetWindowUserPointer(window));
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
            auto windowPtr = static_cast<MacGlfwWindow *>(glfwGetWindowUserPointer(window));
            std::pair xy(xpos, ypos);
            windowPtr->post(Event(EventType::CursorPosEvent, xy));
        });

        glfwSetScrollCallback(m_nativeWindow, [](GLFWwindow* window, double xoffset, double yoffset){
            auto windowPtr = static_cast<MacGlfwWindow *>(glfwGetWindowUserPointer(window));
            std::pair xy(xoffset, yoffset);
            windowPtr->post(Event(EventType::ScrollEvent, xy));
        });
    }

    MacGlfwWindow::~MacGlfwWindow()
    {

    }

    void MacGlfwWindow::onUpdate()
    {
        m_context->swapBuffer();
    }

    void MacGlfwWindow::getSize(int & w, int & h)
    {
        glfwGetWindowSize(m_nativeWindow, &w, &h);
    }

    void* MacGlfwWindow::GetNativeWindow() const
    {
        return m_nativeWindow;
    }

    Render::Context * MacGlfwWindow::getRenderContext()
    {
        return m_context;
    }

    void MacGlfwWindow::setRenderContext(Render::Context* context)
    {
        delete this->m_context;
        this->m_context = context;
        context->init();
    }

    void MacGlfwWindow::init()
    {
        m_context = HYT::Render::Context::create();
        m_context->init();
    }

    void MacGlfwWindow::post(Event e)
    {
        m_eventDispatcher.post(e, APP_EVENT_QUEUE);
    }
} // namespace HYT
