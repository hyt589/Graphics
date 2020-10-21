#pragma once

#include "global.hpp"
#include "Event.hpp"

namespace HYT
{
    class Layer
    {
    public:
        virtual void init() = 0;
        virtual void onUpdate(float seconds) = 0;
        virtual void terminate() = 0;
        virtual void onEvent(Event &e) = 0;

    protected:
    };
} // namespace HYT
