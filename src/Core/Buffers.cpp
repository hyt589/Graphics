#include "Buffers.hpp"
#include "OpenGL.hpp"
#include <magic_enum.hpp>

namespace HYT::Graphics
{
    std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return std::make_shared<::HYT::OpenGL::VertextBuffer>(size);
            break;

        default:

            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }

    std::shared_ptr<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return std::make_shared<::HYT::OpenGL::VertextBuffer>(vertices, size);
            break;

        default:
            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            return std::make_shared<::HYT::OpenGL::IndexBuffer>(indices, count);
            break;

        default:
            LOG_ERROR("Graphics API: {} is not supported", magic_enum::enum_name(Renderer::getAPI()));
            exit(1);
            break;
        }
    }
} // namespace HYT::Graphics