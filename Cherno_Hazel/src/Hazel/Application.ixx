#include "hzpch.h"

#include "core.h"

export module Application;

import Event;
import Buffer;
import Shader;
import ApplicationEvent;
import VertexArray;
import Window;
import Layer;
import LayerStack;
import ImGuiLayer;
import OrthographicCamera;

export namespace Hazel {

    class HAZEL_API Application {
    public:
        Application();
        virtual ~Application();

        void OnEvent(Event&);

        virtual void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        inline Window& GetWindow() { return *m_Window; }

        inline static Application& Get() { return *s_Instance; }

    protected:
        bool m_Running = true;
        std::unique_ptr<Hazel::Window> m_Window;

        Hazel::ImGuiLayer* m_ImGuiLayer;
        Hazel::LayerStack m_LayerStack;

        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr<VertexArray> m_SquareVA;

        OrthographicCamera m_Camera;

    private:
        bool OnWindowCloseEvent(WindowCloseEvent& event);
        bool OnWindowResizeEvent(WindowResizeEvent& event);

    private:
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
} // namespace Hazel
