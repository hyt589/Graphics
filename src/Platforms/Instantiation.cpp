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

#ifdef HYT_PLATFORM_MAC_OS
            s_Instance = new MacGlfwInput();
#endif // HYT_PLATFORM_MAC_OS

            break;
        }
        default:
        {
            LOG_ERROR("Fatal error: Window API: {} not supported", std::string(magic_enum::enum_name(Window::getAPI())));
            exit(1);
            break;
        }
        }
    }

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

    Graphics::Shader *Graphics::Shader::create(std::initializer_list<ShaderSrc> shaderList)
    {
        switch (Graphics::Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return new OpenGL::Shader(shaderList);
            break;

        default:
            break;
        }
        return nullptr;
    }

} // namespace HYT

namespace HYT::Graphics
{
    Context *Context::create()
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::none:
            LOG_ERROR("No graphics API specified");
            LOG_ERROR("Call HYT::Graphics::Renderer::setAPI to specify an API before instantiating an application");
            exit(1);

        case GraphicsAPI::opengl:
            return new ::HYT::OpenGL::Context(static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow()));
            break;

        case GraphicsAPI::vulkan:

#ifdef HYT_PLATFORM_MAC_OS
            LOG_ERROR("Mac OS does not support Vulkan");
            exit(1);
#endif // HYT_PLATFORM_MAC_OS

            break;
        case GraphicsAPI::dx11:
#ifndef HYT_PLATFORM_WIN
            LOG_ERROR("DirectX 11 is only supported on Windows platforms");
            exit(1);
#endif // !HYT_PLATFORM_WIN
            break;
        default:
            LOG_ERROR("Fatal error: Graphics API: {} not supported", std::string(magic_enum::enum_name(Renderer::getAPI())));
            exit(1);
            break;
        }
        return nullptr;
    }
} // namespace HYT::Graphics
