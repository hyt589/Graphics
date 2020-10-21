#include "Application.hpp"
#include "Timer.hpp"

namespace HYT
{
    EventQueue Application::s_eventQueue;
    Application * Application::s_instance;

    Application::Application()
    {
        if (!s_instance)
        {
            Logger::init();
            s_instance = this;
            LOG_INFO("Application instantiated.");
        }
        else
        {
            LOG_WARN("Application already exists!");
        }
    }


    EventQueue &Application::getEventQueue()
    {
        return s_eventQueue;
    }

    void Application::pushLayer(Layer *layer)
    {
        m_layers.emplace_back(layer);
        layer->init();
    }

    void Application::popLayer(Layer *layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            layer->terminate();
            m_layers.erase(it);
        }
    }

    void Application::pushOverlay(Layer *layer)
    {
        m_overlays.emplace_back(layer);
        layer->init();
    }

    void Application::popOverlay(Layer *layer)
    {
        auto it = std::find(m_overlays.begin(), m_overlays.end(), layer);
        if (it != m_overlays.end())
        {
            layer->terminate();
            m_overlays.erase(it);
        }
    }

    void Application::run()
    {
        if (!m_initialized)
        {
            LOG_ERROR("Application not initialized");
            return;
        }
        while (m_shouldRun)
        {
            auto now = Timer::now();
            float dt = Timer::ellapsedSeconds(m_LastFrameTime, now);
            m_LastFrameTime = now;

            for (auto layer : m_layers)
            {
                layer->onUpdate(dt);
            }

            for (auto overlay : m_overlays)
            {
                overlay->onUpdate(dt);
            }

            m_window->onUpdate();
        }
    }
} // namespace HYT
