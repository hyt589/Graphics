#pragma once

#include "global.hpp"
#include "VertexArray.hpp"

namespace HYT::Graphics
{
    class RenderCommands
    {
    public:
        virtual ~RenderCommands() = default;

        virtual void init() = 0;
        virtual void setClearColor(float r, float g, float b, float a) = 0;
        virtual void clear(int bits) = 0;
        virtual void setViewPort(int x, int y, int width, int height) = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count = 0) = 0;

        static std::unique_ptr<RenderCommands> create();
        
    };
} // namespace HYT
