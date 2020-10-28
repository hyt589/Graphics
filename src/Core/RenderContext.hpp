#pragma once

#include "global.hpp"

namespace HYT::Renderer
{
    class Context
    {
        public:
        // Context(){};
        virtual void init() = 0;
        virtual void swapBuffer() = 0;
        static Context * createContext();
    };
} // namespace HYT::Renderer
