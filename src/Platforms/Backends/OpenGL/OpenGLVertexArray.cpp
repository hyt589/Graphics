#include "OpenGLVertexArray.hpp"
#include <magic_enum.hpp>


namespace HYT::OpenGL
{
    using namespace HYT;

    static GLenum ElementOpenGLBaseType(Graphics::ElementDataType type)
    {
        switch (type)
		{
			case Graphics::ElementDataType::Float:    return GL_FLOAT;
			case Graphics::ElementDataType::Float2:   return GL_FLOAT;
			case Graphics::ElementDataType::Float3:   return GL_FLOAT;
			case Graphics::ElementDataType::Float4:   return GL_FLOAT;
			case Graphics::ElementDataType::Mat3:     return GL_FLOAT;
			case Graphics::ElementDataType::Mat4:     return GL_FLOAT;
			case Graphics::ElementDataType::Int:      return GL_INT;
			case Graphics::ElementDataType::Int2:     return GL_INT;
			case Graphics::ElementDataType::Int3:     return GL_INT;
			case Graphics::ElementDataType::Int4:     return GL_INT;
			case Graphics::ElementDataType::Bool:     return GL_BOOL;
            default:
                LOG_ERROR("[OpenGL] Invalid element data type: {}", magic_enum::enum_name(type));
                return 0;
                break;
		}
    }

    VertexArray::VertexArray() 
    {
        GL(glCreateVertexArrays(1, &m_rendererID));
    }
    
    VertexArray::~VertexArray() 
    {
        GL(glDeleteVertexArrays(1, &m_rendererID));
    }
    
    void VertexArray::bind() const 
    {
        GL(glBindVertexArray(m_rendererID));
    }
    
    void VertexArray::unbind() const 
    {
        GL(glBindVertexArray(0));
    }
    
    void VertexArray::addVertexBuffer(const std::shared_ptr<Graphics::VertexBuffer> & vertexBuffer) 
    {
        HYT_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex Buffer has no layout!");

        GL(glBindVertexArray(m_rendererID));
        vertexBuffer->bind();

        const auto & layout = vertexBuffer->getLayout();
        for(const auto & element : layout)
        {
            uint8_t count = element.getComponentCount();
            for(uint8_t i = 0; i < count; i++)
            {
                GL(glEnableVertexAttribArray(m_vertexBufferIndex));
                GL(glVertexAttribPointer(m_vertexBufferIndex,
                    element.getComponentCount(), 
                    ElementOpenGLBaseType(element.dataType),
                    element.normalized ? GL_TRUE : GL_FALSE,
                    layout.getStride(),
                    (const void*)element.offset));
                m_vertexBufferIndex++;
            }
        }
        m_vertexBuffers.push_back(vertexBuffer);
        GL(glBindVertexArray(0));
    }
    
    void VertexArray::setIndexBuffer(const std::shared_ptr<Graphics::IndexBuffer> & indexBuffer) 
    {
        GL(glBindVertexArray(m_rendererID));
        indexBuffer->bind();
        m_IndexBuffer = indexBuffer;
        GL(glBindVertexArray(0));
    }
}