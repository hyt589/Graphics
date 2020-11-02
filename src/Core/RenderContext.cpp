#include "RenderContext.hpp"
#include "OpenGL.hpp"

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