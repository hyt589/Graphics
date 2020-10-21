#pragma once

#include "global.hpp"
#include "Layer.hpp"
#include "Window.hpp"

namespace HYT
{
    class Application
    {
    public:
        virtual void init(std::string name = "Application", int width = 1280, int height = 720) = 0;
        void pushLayer(Layer *layer);
        void popLayer(Layer *layer);
        void pushOverlay(Layer *layer);
        void popOverlay(Layer *layer);
        void run();

    protected:
        bool m_initialized = false;
        bool m_shouldRun = true;
        EventQueue m_eventQueue;
        std::vector<Layer *> m_layers;
        std::vector<Layer *> m_overlays;
        std::chrono::time_point<std::chrono::steady_clock> m_LastFrameTime;
        std::unique_ptr<Window> m_window;
    };
} // namespace HYT
