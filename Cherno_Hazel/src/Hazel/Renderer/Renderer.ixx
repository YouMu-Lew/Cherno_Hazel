#include "hzpch.h"

export module Renderer;

export namespace Hazel {

    enum class RendererAPI {
        None = 0,
        OpenGL = 1,
    };

    class Renderer {
    public:
        inline static RendererAPI GetAPI() { return s_RendererAPI; }

    private:
        static RendererAPI s_RendererAPI;
    };

    RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;

} // namespace Hazel
