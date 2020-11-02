#include "Window.hpp"
#include "MacGlfw.hpp"

namespace HYT
{
    WindowAPI Window::s_api = WindowAPI::None;
    
    Window *Window::Create(const WindowProps &props, int verMajor, int verMinor)
    {
        Input::init();

        switch (Window::getAPI())
        {
        case WindowAPI::None:
            LOG_ERROR("No window API specified.");
            LOG_ERROR("Call HYT::Window::setAPI to specify a window API before instantiating the application");
            exit(1);
            break;
        case WindowAPI::GLFW:
        {
#ifdef HYT_PLATFORM_MAC_OS
            HYT_ASSERT((verMajor * 100 + verMinor * 10 <= 410), "Apple does not support OpenGL beyond version 4.1");
            return new MacGlfwWindow(props, verMajor, verMinor);
#endif // HYT_PLATFORM_MAC_OS

#ifdef HYT_PLATFORM_WIN
            LOG_ERROR("Windows GLFW has not been implemented yet");
            exit(1);
#endif // HYT_PLATFORM_WIN

#ifdef HYT_PLATFORM_LINUX
            LOG_ERROR("Linux GLFW has not been implemented yet");
            exit(1);
#endif // HYT_PLATFORM_LINUX
            break;
        }

        default:
            LOG_ERROR("Fatal error: Window API: {} not supported", std::string(magic_enum::enum_name(Window::getAPI())));
            exit(1);
            break;
        }

        return nullptr;
    }
}