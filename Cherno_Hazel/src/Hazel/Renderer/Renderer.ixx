#include "hzpch.h"

#include <glm\glm.hpp>

export module Renderer;

import RendererAPI;
import VertexArray;
import Shader;
import OrthographicCamera;

export namespace Hazel {

    class Renderer {
    public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const std::shared_ptr<Shader>& shader,
                           const std::shared_ptr<VertexArray>& vertexArray);

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };

} // namespace Hazel
