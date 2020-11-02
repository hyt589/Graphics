#include "Shader.hpp"
#include "OpenGL.hpp"

namespace HYT
{
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
} // namespace HYT::Graphics
