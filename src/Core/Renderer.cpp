#include "Renderer.hpp"
#include "Application.hpp"

namespace HYT::Graphics
{
    GraphicsAPI Renderer::s_api = GraphicsAPI::none;

    void Renderer::setAPI(GraphicsAPI api)
    {
        if (Application::isRunning())
        {
            EventDispatcher::StaticPost(Event(EventType::GraphicsApiSwitchEvent, s_api), APP_EVENT_QUEUE);
        }
        else
        {
            s_api = api;
        }
    }
} // namespace HYT::Graphics
