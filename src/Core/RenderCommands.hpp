#pragma once

#include "global.hpp"
#include "VertexArray.hpp"

namespace HYT::Graphics
{
    class RenderBackend
    {
    public:
        virtual ~RenderBackend() = default;

        virtual void init() = 0;
        virtual void setClearColor(float r, float g, float b, float a) = 0;
        virtual void clear(int bits) = 0;
        virtual void setViewPort(int x, int y, int width, int height) = 0;

        virtual void drawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count = 0) = 0;

        static std::unique_ptr<RenderBackend> create();
        
    };

    class RenderCommands
    {
        public:
        static void Init();
        static void SetClearColor(float r, float g, float b, float a);
        static void Clear(int bits);
        static void SetViewport(int x, int y, int width, int height);
        static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray, uint32_t count = 0);
        private:
        static std::unique_ptr<RenderBackend> s_backend;
    };
} // namespace HYT
