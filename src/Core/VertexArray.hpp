#pragma once

#include "global.hpp"
#include "Buffers.hpp"

namespace HYT::Graphics
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void addVertexBuffer(const Shared<VertexBuffer> & vertexBuffer) = 0;
        virtual void setIndexBuffer(const Shared<IndexBuffer> & indexBuffer) = 0;

        virtual const std::vector<Shared<VertexBuffer>> & getVertexBuffer() const = 0;
        virtual const Shared<IndexBuffer> & getIndexBuffer() const = 0;

        static Shared<VertexArray> create();
    };
} // namespace HYT::Graphics
