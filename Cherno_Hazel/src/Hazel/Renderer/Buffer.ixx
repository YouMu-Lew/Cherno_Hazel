#include "hzpch.h"

export module Buffer;

namespace Hazel {
    export enum class ShaderDataType { None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool };

    static uint32_t ShaderDataTypeSize(const ShaderDataType& type)
    {
        switch (type) {
            case ShaderDataType::Float: return 4;
            case ShaderDataType::Float2: return 4 * 2;
            case ShaderDataType::Float3: return 4 * 3;
            case ShaderDataType::Float4: return 4 * 4;
            case ShaderDataType::Mat3: return 4 * 3 * 3;
            case ShaderDataType::Mat4: return 4 * 4 * 4;
            case ShaderDataType::Int: return 4;
            case ShaderDataType::Int2: return 4 * 2;
            case ShaderDataType::Int3: return 4 * 3;
            case ShaderDataType::Int4: return 4 * 4;
            case ShaderDataType::Bool: return 1;
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
        bool Normalized;
        uint32_t Size;
        uint32_t Offset;

        BufferLayoutElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Type(type), Name(name), Normalized(normalized), Size(ShaderDataTypeSize(type)), Offset(0)
        {
        }

        inline const uint32_t GetComponentCount() const
        {
            switch (Type) {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3: return 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4;
                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;
                case ShaderDataType::Bool: return 1;
            }
            HZ_CORE_ASSERT(false, "Unknown ShaderDataType.");
            return 0;
        }
    };

    class BufferLayout {
    public:
        BufferLayout() {}

        // TODO: why `initializer_list` can but `vertor` cannot
        BufferLayout(const std::initializer_list<BufferLayoutElement>& elements) : m_elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferLayoutElement>& GetElements() const { return m_elements; }
        inline const uint32_t GetStride() const { return m_stride; }

    private:
        inline void CalculateOffsetsAndStride()
        {
            // TODO: why need `uint32_t offset`, I think `m_stride` is enough.
            // In my opinion, They are the same.
            m_stride = 0;
            uint32_t offset = 0;
            for (auto& element : m_elements) {
                element.Offset = offset;
                offset += element.Size;
                m_stride += element.Size;
            }
        }

    private:
        uint32_t m_stride;
        std::vector<BufferLayoutElement> m_elements;
    };

    class VertexBuffer {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

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
