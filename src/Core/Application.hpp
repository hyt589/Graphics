#pragma once

#include "global.hpp"
#include "Layer.hpp"

namespace HYT
{
    class Application
    {
    public:
        virtual void init();
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
    };
} // namespace HYT
