#include "Instantiation.hpp"

namespace HYT
{

    Input *Input::s_Instance;

    void Input::init()
    {
        switch (g_window_api)
        {
        case WindowAPI::GLFW:
        {
#ifdef __APPLE__
            s_Instance = new MacGlfwInput();
#endif // __APPLE__
            break;
        }
        default:
        {
            LOG_ERROR("Unsupported windowing api");
            exit(1);
            break;
        }
        }
    }

    Window *Window::Create(const WindowProps &props, int verMajor, int verMinor)
    {
        Input::init();

        switch (g_window_api)
        {
        case WindowAPI::GLFW:
        {
#ifdef __APPLE__
            HYT_ASSERT((verMajor * 100 + verMinor * 10 <= 410), "Apple does not support OpenGL beyond version 4.1");
            return new MacGlfwWindow(props, verMajor, verMinor);
#endif // __APPLE__
            break;
        }

        default:
            break;
        }
    }
} // namespace HYT


namespace HYT::Render
{
    Context * Context::create()
    {
        switch (Renderer::getAPI())
        {
        case RenderAPI::opengl :
            return new ::HYT::OpenGL::Context(static_cast<GLFWwindow*>(APP_WINDOW->GetNativeWindow()));
            break;
        default:
            break;
        }
        return nullptr;
    }
} // namespace HYT::Renderer
