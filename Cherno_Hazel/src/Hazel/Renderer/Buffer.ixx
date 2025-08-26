#include "hzpch.h"

export module Buffer;

export namespace Hazel {

    enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

}

namespace Hazel {

    static uint32_t ShaderDataTypeSize(const ShaderDataType& type)
    {
        switch (type) {
            case Hazel::ShaderDataType::Float:
                return 4;
            case ShaderDataType::Float2:
                return 4 * 2;
            case ShaderDataType::Float3:
                return 4 * 3;
            case ShaderDataType::Float4:
                return 4 * 4;
            case ShaderDataType::Mat3:
                return 4 * 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4 * 4;
            case ShaderDataType::Int:
                return 4;
            case ShaderDataType::Int2:
                return 4 * 2;
            case ShaderDataType::Int3:
                return 4 * 3;
            case ShaderDataType::Int4:
                return 4 * 4;
            case ShaderDataType::Bool:
                return 1;
        }
        HZ_CORE_ASSERT(false, "Unknown ShaderDataType.");
        return 0;
    }

    static uint32_t ShaderDataTypeCount(const ShaderDataType& type)
    {
        switch (type) {
            case Hazel::ShaderDataType::Float:
                return 1;
            case ShaderDataType::Float2:
                return 2;
            case ShaderDataType::Float3:
                return 3;
            case ShaderDataType::Float4:
                return 4;
            case ShaderDataType::Mat3:
                return 3 * 3;
            case ShaderDataType::Mat4:
                return 4 * 4;
            case ShaderDataType::Int:
                return 1;
            case ShaderDataType::Int2:
                return 2;
            case ShaderDataType::Int3:
                return 3;
            case ShaderDataType::Int4:
                return 4;
            case ShaderDataType::Bool:
                return 1;
        }
        HZ_CORE_ASSERT(false, "Unknown ShaderDataType.");
        return 0;
    }

} // namespace Hazel

export namespace Hazel {

    // enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

    struct BufferLayoutElement
    {
        ShaderDataType Type;
        std::string Name;
        uint32_t Size;
        uint32_t Offset;
        uint32_t Count;
        bool Normalized;

        BufferLayoutElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Type(type), Name(name), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0),
              Count(ShaderDataTypeCount(type))
        {
        }
    };

    class VertexBufferLayout {
    public:
        VertexBufferLayout() {}

        // TODO: why `initializer_list` can but `vertor` cannot
        VertexBufferLayout(const std::initializer_list<BufferLayoutElement>& elements)
        {
            // TODO: why need `uint32_t offset`, I think `m_stride` is enough.
            // In my apnion, They are the same.
            m_stride = 0;
            uint32_t offset = 0;
            for (const auto& element : elements) {
                BufferLayoutElement e(element.Type, element.Name);
                e.Offset = offset;
                offset += e.Size;
                m_stride += e.Size;
                m_elements.push_back(e);
            }
        }

        inline const std::vector<BufferLayoutElement>& GetElements() const { return m_elements; }
        inline const uint32_t GetStride() const { return m_stride; }

    private:
        uint32_t m_stride;
        std::vector<BufferLayoutElement> m_elements;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const VertexBufferLayout& layout) = 0;
        virtual const VertexBufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t count);
    };

} // namespace Hazel
