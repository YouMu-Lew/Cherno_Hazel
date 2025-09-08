#include "hzpch.h"

#include <glm\glm.hpp>

export module RendererAPI;

import VertexArray;

export namespace Hazel {

    class RendererAPI {
    public:
        enum class API {
            None = 0,
            OpenGL = 1,
        };

    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return s_API; }

    private:
        static API s_API;
    };

    /**
     * implement
     */
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

} // namespace Hazel