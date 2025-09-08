#include "hzpch.h"

module Renderer;

import RenderCommand;

namespace Hazel {

    void Renderer::BeginScene() {}
    void Renderer::EndScene() {}

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace Hazel