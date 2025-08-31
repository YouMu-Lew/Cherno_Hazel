#include "hzpch.h"

module VertexArray;

import Renderer;
import OpenGLVertexArray;

namespace Hazel {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::None:
            {
                HZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
                return nullptr;
            }
            case RendererAPI::OpenGL:
            {
                return new OpenGLVertexArray();
            }
        }

        HZ_CORE_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

} // namespace Hazel