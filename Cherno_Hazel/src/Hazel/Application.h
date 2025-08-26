#pragma once

#include "core.h"
#include "Window.h"

#include "Hazel\LayerStack.h"
#include "Hazel\ImGui\ImGuiLayer.h"

import Event;
import Buffer;
import Shader;
import ApplicationEvent;

namespace Hazel {

    class HAZEL_API Application {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event&);

        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }

        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowCloseEvent(WindowCloseEvent& event);
        bool OnWindowResizeEvent(WindowResizeEvent& event);

        std::unique_ptr<Hazel::Window> m_Window;
        Hazel::ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        Hazel::LayerStack m_LayerStack;

        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
} // namespace Hazel
