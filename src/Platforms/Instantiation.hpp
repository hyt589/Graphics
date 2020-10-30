#include "Core.hpp"
#include "OpenGL.hpp"
#include "MacGlfw.hpp"

namespace HYT
{

    Render::Shader * Render::Shader::create(std::initializer_list<ShaderSrc> shaderList)
    {
        switch (Render::Renderer::getAPI())
        {
        case RenderAPI::opengl :
            return new OpenGL::Shader(shaderList);
            break;
        
        default:
            break;
        }
        return nullptr;
    }
} // namespace HYT
