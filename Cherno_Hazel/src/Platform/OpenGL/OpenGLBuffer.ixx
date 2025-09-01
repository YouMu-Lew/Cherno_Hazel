#include "hzpch.h"

#include <glad\glad.h>

export module OpenGLBuffer;

import Buffer;

export namespace Hazel {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        virtual const BufferLayout& GetLayout() const override { return m_Layout; }

    private:
        uint32_t m_RendererID;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

        virtual uint32_t GetCount() const { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
    };

} // namespace Hazel

/**
 * Implementation
 */

namespace Hazel {

    /**
     * VertexBuffer
     */

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        // 生成一个顶点缓冲对象（VBO），用于存储顶点数据
        glCreateBuffers(1, &m_RendererID);

        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

        // 将顶点数据上传到GPU内存中，GL_STATIC_DRAW 表示数据在绘制过程中不会频繁更改
        glNamedBufferData(m_RendererID, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        // 将VBO绑定到GL_ARRAY_BUFFER目标上，表示这是一个顶点数据缓冲
        glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /**
     * IndexBuffer
     */

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
    {
        // 生成一个索引缓冲对象（EBO），用于存储索引数据
        glCreateBuffers(1, &m_RendererID);
        // 将EBO绑定到GL_ELEMENT_ARRAY_BUFFER目标上，表示这是一个索引缓冲
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
        // 将索引数据上传到GPU内存中，GL_STATIC_DRAW表示数据在绘制过程中不会频繁更改
        glNamedBufferData(m_RendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_RendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

} // namespace Hazel