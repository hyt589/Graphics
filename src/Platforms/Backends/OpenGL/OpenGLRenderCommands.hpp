#pragma once

#include "gl_base.hpp"
#include "Core.hpp"

namespace HYT::OpenGL
{

    class RenderCommands : public ::HYT::Graphics::RenderCommands
    {
    public:
        virtual ~RenderCommands() = default;

        virtual void init() override;
        virtual void setClearColor(float r, float g, float b, float a) override;
        virtual void clear(int bits) override;
        virtual void setViewPort(int x, int y, int width, int height) override;

        virtual void drawIndexed(const std::shared_ptr<::HYT::Graphics::VertexArray> &vertexArray, uint32_t count = 0) override;
    };
} // namespace HYT::OpenGL
