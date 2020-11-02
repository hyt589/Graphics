#pragma once

#include "Log.hpp"
#include <magic_enum.hpp>

namespace HYT
{
    enum class ElementDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static constexpr uint32_t ElementDataTypeSize(ElementDataType type)
    {
        switch (type)
		{
            case ElementDataType::None:     break;
			case ElementDataType::Float:    return 4;
			case ElementDataType::Float2:   return 4 * 2;
			case ElementDataType::Float3:   return 4 * 3;
			case ElementDataType::Float4:   return 4 * 4;
			case ElementDataType::Mat3:     return 4 * 3 * 3;
			case ElementDataType::Mat4:     return 4 * 4 * 4;
			case ElementDataType::Int:      return 4;
			case ElementDataType::Int2:     return 4 * 2;
			case ElementDataType::Int3:     return 4 * 3;
			case ElementDataType::Int4:     return 4 * 4;
			case ElementDataType::Bool:     return 1;
		}

        LOG_ERROR("[CORE] Unknown buffer element data type: {}", magic_enum::enum_name(type));
        return 0;
    };

    struct BufferElement
    {
        std::string name;
        ElementDataType dataType;
        uint32_t size;
        size_t offset;
        bool normalized;

        BufferElement() = default;

        BufferElement(ElementDataType p_type, const std::string & p_name, bool p_normalized = false)
            : name(p_name), dataType(p_type), normalized(p_normalized)
        {};

        uint32_t getComponentCount() const
        {
            switch (dataType)
			{
                case ElementDataType::None:     break;
				case ElementDataType::Float:   return 1;
				case ElementDataType::Float2:  return 2;
				case ElementDataType::Float3:  return 3;
				case ElementDataType::Float4:  return 4;
				case ElementDataType::Mat3:    return 3 * 3; // 3* float3
				case ElementDataType::Mat4:    return 4 * 4; // 4* float4
				case ElementDataType::Int:     return 1;
				case ElementDataType::Int2:    return 2;
				case ElementDataType::Int3:    return 3;
				case ElementDataType::Int4:    return 4;
				case ElementDataType::Bool:    return 1;
			}

            LOG_ERROR("[CORE] Unknown buffer element data type: {}", magic_enum::enum_name(dataType));
            return 0;
        };
    };

    class BufferLayout
    {
    public:
        BufferLayout(){}

        BufferLayout(std::initializer_list<BufferElement> elements)
            : m_elements(elements)
        {
            calculateOffsetsAndStride();
        }

        uint32_t getStride() const {return m_stride;}
        const std::vector<BufferElement>& GetElements() const {return m_elements;}

        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

    private:

        void calculateOffsetsAndStride()
		{
			size_t offset = 0;
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.offset = offset;
				offset += element.size;
				m_stride += element.size;
			}
		}

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;

    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void sendData(const void * data, uint32_t size) = 0;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(BufferLayout& layout) = 0;

        static std::shared_ptr<VertexBuffer> Create(uint32_t size);
        static std::shared_ptr<VertexBuffer> Create(float * vertices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
		virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;

        static std::shared_ptr<IndexBuffer> Create(uint32_t * indices, uint32_t count);

    };

} // namespace HYT
