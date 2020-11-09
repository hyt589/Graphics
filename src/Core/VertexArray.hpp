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

        virtual void addVertexBuffer(const RefCounted<VertexBuffer> & vertexBuffer) = 0;
        virtual void setIndexBuffer(const RefCounted<IndexBuffer> & indexBuffer) = 0;

        virtual const std::vector<RefCounted<VertexBuffer>> & getVertexBuffer() const = 0;
        virtual const RefCounted<IndexBuffer> & getIndexBuffer() const = 0;

        static RefCounted<VertexArray> create();
    };
} // namespace HYT::Graphics
