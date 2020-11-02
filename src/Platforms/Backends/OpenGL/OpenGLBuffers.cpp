#include "OpenGLBuffers.hpp"

namespace HYT::OpenGL
{

    using ::HYT::Graphics::BufferLayout;

    VertextBuffer::VertextBuffer(uint32_t size) 
    {
        GL(glCreateBuffers(1, &m_rendererID));
        GL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
        GL(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
        GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    
    VertextBuffer::VertextBuffer(float *vertices, uint32_t size) 
    {
        GL(glCreateBuffers(1, &m_rendererID));
        GL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
        GL(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_DYNAMIC_DRAW));
        GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    VertextBuffer::~VertextBuffer() 
    {
        GL(glDeleteBuffers(1, &m_rendererID));
    }

    void VertextBuffer::bind() const 
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    }
    
    void VertextBuffer::unbind() const 
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    
    void VertextBuffer::sendData(const void *data, uint32_t size) 
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
		GL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
        GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    
    IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count) 
    {
        GL(glCreateBuffers(1, &m_rendererID));
        GL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
        GL(glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW));
        GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    
    IndexBuffer::~IndexBuffer() 
    {
        GL(glDeleteBuffers(1, &m_rendererID));
    }
    
    void IndexBuffer::bind() const 
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    }
    
    void IndexBuffer::unbind() const 
    {
        GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    
} // namespace HYT::OpenGL
