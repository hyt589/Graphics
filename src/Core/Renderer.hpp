#pragma once

#include "global.hpp"

namespace HYT::Render
{
    class Renderer
    {
    public:
        inline static GraphicsAPI getAPI() {return s_api;};
        static void setAPI(GraphicsAPI api);
    private:
        static GraphicsAPI s_api;
    };
} // namespace HYT::Render
