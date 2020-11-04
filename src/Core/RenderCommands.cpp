#include "RenderCommands.hpp"
#include "Renderer.hpp"

namespace HYT::Graphics
{
    std::unique_ptr<RenderCommands> RenderCommands::create()
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            
            break;
        
        default:
            break;
        }
    }
} // namespace HYT
