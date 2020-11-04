#pragma once

#include "global.hpp"
#include "VertexArray.hpp"

namespace HYT::Graphics
{
    class Renderer
    {
    public:
        virtual ~Renderer() = default;

        virtual void init() = 0;
        virtual void setClearColor(float r, float g, float b, float a) = 0;
        virtual void clear() = 0;
        virtual void setViewPort(int x, int y, int w, int h) = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count = 0) = 0;

        inline static GraphicsAPI getAPI() { return s_api; };
        static void setAPI(GraphicsAPI api);

    private:
        static GraphicsAPI s_api;
    };
} // namespace HYT::Graphics
