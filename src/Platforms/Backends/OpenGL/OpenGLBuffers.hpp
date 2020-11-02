#pragma once

#include "gl_base.hpp"
#include "Core.hpp"

namespace HYT::OpenGL
{
    using ::HYT::Graphics::BufferLayout;

    class VertextBuffer : public ::HYT::Graphics::VertexBuffer
    {
    public:
        VertextBuffer(uint32_t size);
        VertextBuffer(float *vertices, uint32_t size);
        virtual ~VertextBuffer();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void sendData(const void *data, uint32_t size) override;

        virtual const BufferLayout &getLayout() const override { return m_layout; }
        virtual void setLayout(BufferLayout &layout) override { m_layout = layout; }

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };

    class IndexBuffer : public ::HYT::Graphics::IndexBuffer
    {
    public:
        IndexBuffer(uint32_t *indices, uint32_t count);
        virtual ~IndexBuffer();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual uint32_t getCount() const override { return m_count; }

    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };
} // namespace HYT::OpenGL
