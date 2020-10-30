#pragma once

#include "global.hpp"

namespace HYT::Render
{
    class Renderer
    {
    public:
        inline static RenderAPI getAPI() {return s_api;};
        static void setAPI(RenderAPI api);
    private:
        static RenderAPI s_api;
    };
} // namespace HYT::Render
