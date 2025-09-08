#include "hzpch.h"

module VertexArray;

import Renderer;
import OpenGLVertexArray;

namespace Hazel {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::API::None:
            {
                HZ_CORE_ASSERT(false, "RendererAPI::API::None is currently not supported.");
                return nullptr;
            }
            case RendererAPI::API::OpenGL:
            {
                return new OpenGLVertexArray();
            }
        }

        HZ_CORE_ASSERT(false, "Unknown RendererAPI.");
        return nullptr;
    }

} // namespace Hazel