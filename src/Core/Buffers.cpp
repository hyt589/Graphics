#include "Buffers.hpp"
#include "OpenGL.hpp"
#include <magic_enum.hpp>

namespace HYT::Graphics
{
    RefCounted<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return CreateRefCounted<::HYT::OpenGL::VertextBuffer>(size);
            break;

        default:
            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }

    RefCounted<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return CreateRefCounted<::HYT::OpenGL::VertextBuffer>(vertices, size);
            break;

        default:
            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }

    RefCounted<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return CreateRefCounted<::HYT::OpenGL::IndexBuffer>(indices, count);
            break;

        default:
            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }
} // namespace HYT::Graphics