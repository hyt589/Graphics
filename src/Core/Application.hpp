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
        Application();
        virtual ~Application() {};
        virtual void init(std::string name = "Application", int width = 1280, int height = 720){};
        void pushLayer(Layer *layer);
        void popLayer(Layer *layer);
        void pushOverlay(Layer *layer);
        void popOverlay(Layer *layer);
        void run();

        static EventQueue & getEventQueue();

    protected:
        bool m_initialized = false;
        bool m_shouldRun = true;
        std::vector<Layer *> m_layers;
        std::vector<Layer *> m_overlays;
        std::chrono::time_point<std::chrono::steady_clock> m_LastFrameTime;
        std::unique_ptr<Window> m_window;
        static EventQueue s_eventQueue;
        static Application * s_instance;
    };
} // namespace HYT
