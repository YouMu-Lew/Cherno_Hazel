#include "hzpch.h"

export module Renderer;

import RendererAPI;
import VertexArray;

export namespace Hazel {

    class Renderer {
    public:
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    };

} // namespace Hazel
