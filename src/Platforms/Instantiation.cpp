#include "Instantiation.hpp"

namespace HYT
{

    Input *Input::s_Instance;

    void Input::init()
    {
        switch (Window::getAPI())
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

    WindowAPI Window::s_api;

    Window *Window::Create(const WindowProps &props, int verMajor, int verMinor)
    {
        Input::init();

        switch (Window::getAPI())
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
            LOG_CRITICAL("Fatal error: Window API: {} not supported", std::string(magic_enum::enum_name(Window::getAPI())));
            exit(1);
            break;
        }
    }
} // namespace HYT

namespace HYT::Graphics
{
    Context *Context::create()
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::none:
            LOG_CRITICAL("No graphics API specified");
            LOG_ERROR("Call HYT::Graphics::Renderer::setAPI to specify an API before instantiating an application");
            exit(0);
        case GraphicsAPI::opengl:
            return new ::HYT::OpenGL::Context(static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow()));
            break;
        default:
            LOG_CRITICAL("Fatal error: Graphics API: {} not supported", std::string(magic_enum::enum_name(Renderer::getAPI())));
            exit(1);
            break;
        }
        return nullptr;
    }
} // namespace HYT::Graphics
