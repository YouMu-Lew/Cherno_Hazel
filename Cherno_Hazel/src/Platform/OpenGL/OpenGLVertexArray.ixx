#include "hzpch.h"

import VertexArray;
import Buffer;

#include <glad\glad.h>

export module OpenGLVertexArray;

export namespace Hazel {

    class OpenGLVertexArray : public VertexArray {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        virtual void Bind() override;
        virtual void UnBind() override;

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const override;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override;

    private:
        uint32_t m_RendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };

} // namespace Hazel

/**
 * Implementation
 */

namespace Hazel {

    static GLenum SwitchShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4: return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Bool: return GL_BOOL;
        }
        HZ_CORE_ASSERT(false, "Unknown ShaderDataType.");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        UnBind();
    }

    void OpenGLVertexArray::Bind()
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind()
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        HZ_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        auto& bufferLayout = vertexBuffer->GetLayout();

        int index = 0;
        for (auto& element : bufferLayout.GetElements()) {
            // 启用顶点属性索引 index，表示该属性将被传递给着色器
            glEnableVertexAttribArray(index);
            // 配置顶点属性指针，定义如何从VBO中读取顶点数据：
            // - 索引为0
            // - 每个顶点包含3个分量（x, y, z）
            // - 数据类型为GL_FLOAT
            // - 不进行归一化处理（GL_FALSE）
            // - 顶点之间的步长为3 * sizeof(float)
            // - 数据偏移量为nullptr（从缓冲区的起始位置开始）
            // clang-format off
            glVertexAttribPointer(
                index, 
                element.GetComponentCount(), 
                SwitchShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE, 
                bufferLayout.GetStride(), 
                (const void*)element.Offset
            );
            // clang-format on
            ++index;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        m_indexBuffer = indexBuffer;
    }

    const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const
    {
        return m_VertexBuffers;
    }

    const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
    {
        return m_indexBuffer;
    }

} // namespace Hazel