#include "Renderer.hpp"
#include "Application.hpp"

namespace HYT::Render
{
    RenderAPI Renderer::s_api = RenderAPI::opengl;

    void Renderer::setAPI(RenderAPI api)
    {
        s_api = api;
        if(APP_INSTANCE->isInitialized())
        {
            APP_WINDOW->setRenderContext(Context::create());
        }
    }
} // namespace HYT::Render
