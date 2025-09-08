#include "hzpch.h"

module RenderCommand;

import OpenGLRendererAPI;

namespace Hazel {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

} // namespace Hazel