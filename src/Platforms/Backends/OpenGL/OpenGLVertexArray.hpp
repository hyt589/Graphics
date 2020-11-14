#pragma once

#include "gl_base.hpp"

namespace HYT::OpenGL
{
    using namespace HYT;
    
    class VertexArray : public Graphics::VertexArray
    {
    public:
        VertexArray();
        virtual ~VertexArray();

        virtual void bind() const override;
        virtual void unbind() const override;

        virtual void addVertexBuffer(const Shared<Graphics::VertexBuffer> & vertexBuffer) override;
        virtual void setIndexBuffer(const Shared<Graphics::IndexBuffer> & indexBuffer) override;
        
        virtual const std::vector<Shared<Graphics::VertexBuffer>> & getVertexBuffer() const override { return m_vertexBuffers; }
        virtual const Shared<Graphics::IndexBuffer> & getIndexBuffer() const override { return m_IndexBuffer; }
    private:
        uint32_t m_rendererID;
		uint32_t m_vertexBufferIndex = 0;
		std::vector<Shared<Graphics::VertexBuffer>> m_vertexBuffers;
		Shared<Graphics::IndexBuffer> m_IndexBuffer;
    };
} // namespace HYT::OpenGL
