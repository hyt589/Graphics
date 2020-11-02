#include "VertexArray.hpp"
#include "Log.hpp"
#include "Renderer.hpp"
#include "OpenGL.hpp"
#include <magic_enum.hpp>

namespace HYT::Graphics
{
    using namespace HYT;

    std::shared_ptr<VertexArray> VertexArray::create() 
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return std::make_shared<OpenGL::VertexArray>();
            break;
        
        default:
            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
        
    }
}