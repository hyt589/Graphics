#include "RenderCommands.hpp"
#include "Renderer.hpp"
#include "OpenGL.hpp"
#include <magic_enum.hpp>

namespace HYT::Graphics
{
    std::unique_ptr<RenderCommands> RenderCommands::create()
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return std::make_unique<::HYT::OpenGL::RenderCommands>();
            break;
        
        default:
            LOG_ERROR("[CORE] Unsupported graphics API: {}", magic_enum::enum_name(Renderer::getAPI()));
            return NULL;
            break;
        }
    }
} // namespace HYT
