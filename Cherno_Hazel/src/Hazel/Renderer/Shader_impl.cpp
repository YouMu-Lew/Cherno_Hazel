#include "hzpch.h"

module Shader;

import Renderer;
import OpenGLShader;

namespace Hazel {

    Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI()) {
            case (RendererAPI::None):
            {
                HZ_CORE_ASSERT(false, "RendererAPI::None is not supported now.");
                return nullptr;
            }
            case RendererAPI::OpenGL:
            {
                return new OpenGLShader(vertexSrc, fragmentSrc);
            }
        }

        HZ_CORE_ASSERT(false, "RendererAPI is unknown.");
        return nullptr;
    }

} // namespace Hazel