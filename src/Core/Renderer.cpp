#include "Renderer.hpp"
#include "Application.hpp"

namespace HYT::Render
{
    GraphicsAPI Renderer::s_api = GraphicsAPI::none;

    void Renderer::setAPI(GraphicsAPI api)
    {
        s_api = api;
        if(Application::isRunning())
        {
            APP_WINDOW->setRenderContext(Context::create());
        }
    }
} // namespace HYT::Render
