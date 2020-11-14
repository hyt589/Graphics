#include "Shader.hpp"
#include "OpenGL.hpp"

namespace HYT
{
    Shared<Graphics::Shader> Graphics::Shader::create(std::initializer_list<ShaderSrc> shaderList)
    {
        switch (Graphics::Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return  CreateShared<OpenGL::Shader>(shaderList);
            break;

        default:
            HYT_ASSERT(false, "Graphics API: {} not supported", magic_enum::enum_name(Graphics::Renderer::getAPI()));
            break;
        }
        return nullptr;
    }
} // namespace HYT::Graphics
