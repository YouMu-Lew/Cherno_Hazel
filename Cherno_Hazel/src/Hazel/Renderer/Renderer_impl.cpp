#include "hzpch.h"

module Renderer;

import RenderCommand;
import OrthographicCamera;

namespace Hazel {

    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

    void Renderer::BeginScene(const OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(const std::shared_ptr<Shader>& shader,
                          const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

} // namespace Hazel