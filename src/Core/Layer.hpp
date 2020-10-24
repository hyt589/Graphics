#pragma once

#include "global.hpp"
#include "Event.hpp"

namespace HYT
{
    class Layer
    {
    public:
        virtual void init() {};
        virtual void onUpdate(float seconds) {};
        virtual void terminate() {};
        virtual void onEvent(Event &e) {};
        inline void subscribe(EventType type, std::function<bool(Event&)> callback)
        {
            m_eventDispatcher.subscribe(type, callback);
        };

    protected:
        EventDispatcher m_eventDispatcher;
    };
} // namespace HYT
