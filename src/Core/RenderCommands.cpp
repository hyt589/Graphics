#include "RenderCommands.hpp"
#include "Renderer.hpp"
#include "OpenGL.hpp"
#include <magic_enum.hpp>

namespace HYT::Graphics
{
    std::unique_ptr<RenderBackend> RenderBackend::create()
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return std::make_unique<::HYT::OpenGL::RenderBackend>();
            break;
        
        default:
            LOG_ERROR("[CORE] Unsupported graphics API: {}", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }
    
    std::unique_ptr<RenderBackend> RenderCommands::s_backend;

    void RenderCommands::Init() 
    {
        if(!s_backend)
        {
            s_backend = RenderBackend::create();
        }
        s_backend->init();
    }
    
    void RenderCommands::SetClearColor(float r, float g, float b, float a) 
    {
        s_backend->setClearColor(r, g, b, a);
    }
    
    void RenderCommands::Clear(int bits) 
    {
        s_backend->clear(bits);
    }
    
    void RenderCommands::SetViewport(int x, int y, int width, int height) 
    {
        s_backend->setViewPort(x, y, width, height);
    }
    
    void RenderCommands::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count) 
    {
        s_backend->drawIndexed(vertexArray, count);
    }
} // namespace HYT
