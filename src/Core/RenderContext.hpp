#pragma once

#include "global.hpp"

namespace HYT::Render
{
    class Context
    {
        public:
        // Context(){};
        virtual ~Context(){};
        virtual void init() = 0;
        virtual void swapBuffer() = 0;
        
        static Context * create();
    };
} // namespace HYT::Renderer
