#pragma once

import Buffer;

namespace Hazel {

    class OpenGLVertexBuffer : public VertexBuffer {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual void SetLayout(const VertexBufferLayout& layout) override { m_layout = layout; }
        virtual const VertexBufferLayout& GetLayout() const override { return m_layout; }

    private:
        uint32_t m_RendererID;
        VertexBufferLayout m_layout;
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
