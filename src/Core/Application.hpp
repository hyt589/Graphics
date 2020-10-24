#pragma once

#include "global.hpp"
#include "Layer.hpp"
#include "Window.hpp"
#include "Log.hpp"

namespace HYT
{
    class Application
    {
    public:
        virtual ~Application() {};
        void pushLayer(Layer *layer);
        void popLayer(Layer *layer);
        void pushOverlay(Layer *layer);
        void popOverlay(Layer *layer);
        void subscribe(EventType, std::function<bool(Event &)>);
        void shouldRun(bool should);
        void run();

        EventQueue & getEventQueue();
        static Application * getInstance(const std::string& name = "OpenGL Sandbox", uint32_t width = 1280, uint32_t height = 720);

    protected:
        void handleEvents();
        Application() = default;

        bool m_initialized = false;
        bool m_shouldRun = true;
        std::vector<Layer *> m_layers;
        std::vector<Layer *> m_overlays;
        std::chrono::time_point<std::chrono::steady_clock> m_LastFrameTime;
        std::unique_ptr<Window> m_window;
        EventQueue m_eventQueue;
        EventDispatcher m_dispatcher;
        static Application * s_instance;
    };
} // namespace HYT

#define APP_EVENT_QUEUE ::HYT::Application::getInstance()->getEventQueue()
#define APP_INSTANCE ::HYT::Application::getInstance()
