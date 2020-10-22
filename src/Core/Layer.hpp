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

    protected:
    };
} // namespace HYT
