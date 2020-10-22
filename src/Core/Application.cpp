#include "Application.hpp"
#include "Timer.hpp"

namespace HYT
{
    // EventQueue Application::s_eventQueue;
    Application *Application::s_instance;

    Application::Application(WindowProps &props)
    {
        if (!s_instance)
        {
            Logger::init();
            s_instance = this;

            m_window = std::unique_ptr<Window>(Window::Create(props));
            m_initialized = true;

            m_eventQueue = EventQueue();
            m_LastFrameTime = Timer::now();

            LOG_INFO("[CORE] Application instantiated.");
        }
        else
        {
            LOG_WARN("[CORE] Application already exists!");
        }
    }

    Application *Application::getInstance(const std::string &name, uint32_t width, uint32_t height)
    {
        if (!s_instance)
        {
            WindowProps props(name, width, height);
            Application app(props);
        }
        return s_instance;
    }

    EventQueue &Application::getEventQueue()
    {
        return m_eventQueue;
    }

    void Application::pushLayer(Layer *layer)
    {
        m_layers.push_back(layer);
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
        m_overlays.push_back(layer);
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
        if (m_initialized == false)
        {
            LOG_ERROR("[CORE] Application cannot run before initialization");
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
