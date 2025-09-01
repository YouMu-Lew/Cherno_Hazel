#include "hzpch.h"
#include "core.h"
#include <glad\glad.h>

module Application;

namespace Hazel {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new Hazel::ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
        {
            /**
             * Triangle
             */

            // 生成一个顶点数组对象（VAO），用于保存顶点数据和属性配置的状态
            m_VertexArray.reset(VertexArray::Create());

            // 定义一个包含3个顶点的数组，每个顶点有3个浮点数（x, y, z坐标）
            float vertices[3 * 7] = {
                -0.5f, -0.5f, 0.0f, 0.5f, 0.8f, 0.4f, 0.0f, // 第一个顶点
                -0.0f, 0.5f,  0.0f, 0.0f, 0.1f, 0.3f, 0.0f, // 第二个顶点
                0.5f,  -0.5f, 0.0f, 0.5f, 0.4f, 0.9f, 0.0f, // 第三个顶点
            };

            std::shared_ptr<VertexBuffer> vertexBuffer;
            vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
            {
                BufferLayout layout = {
                    {ShaderDataType::Float3, "a_Position"},
                    {ShaderDataType::Float4, "a_Color"},
                };
                vertexBuffer->SetLayout(layout);
            }
            m_VertexArray->AddVertexBuffer(vertexBuffer);

            // 定义一个包含3个索引的数组，用于指定顶点的绘制顺序
            uint32_t indices[3] = {0, 1, 2};

            std::shared_ptr<IndexBuffer> indexBuffer;
            indexBuffer.reset((IndexBuffer::Create(indices, 3)));
            m_VertexArray->SetIndexBuffer(indexBuffer);

            std::string vertexSrc = R"(
            #version 460 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            out vec3 v_Position;
            out vec4 v_Color;

            void main() {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

            std::string fragmentSrc = R"(
            #version 460 core
            
            layout(location = 0) out vec4 color;
            
            in vec3 v_Position;
            in vec4 v_Color;
            
            void main() {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";

            m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
        }
        {
            /**
             * Square
             */

            m_SquareVA.reset(VertexArray::Create());

            float vertices[3 * 4] = {
                -0.6f, -0.6f, 0.0f, //
                -0.6f, 0.6f,  0.0f, //
                0.6f,  0.6f,  0.0f, //
                0.6f,  -0.6f, 0.0f, //
            };

            std::shared_ptr<VertexBuffer> vertexBuffer;
            vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
            vertexBuffer->SetLayout({
                {ShaderDataType::Float3, "a_Position"},
            });
            m_SquareVA->AddVertexBuffer(vertexBuffer);

            uint32_t indices[6] = {
                0, 1, 2, //
                0, 2, 3, //
            };

            std::shared_ptr<IndexBuffer> indexBuffer;
            indexBuffer.reset((IndexBuffer::Create(indices, 6)));
            m_SquareVA->SetIndexBuffer(indexBuffer);

            std::string vertexSrc = R"(
            #version 460 core
            
            layout(location = 0) in vec3 a_Position;
            
            out vec3 v_Position;

            void main() {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

            std::string fragmentSrc = R"(
            #version 460 core
            
            layout(location = 0) out vec4 color;
            
            in vec3 v_Position;
            
            void main() {
                color = vec4(0.1, 0.1, 0.7, 1.0);
            }
        )";

            m_BlueShader.reset(Shader::Create(vertexSrc, fragmentSrc));
        }
    }

    Application::~Application() {}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowCloseEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResizeEvent));

        // HZ_CORE_INFO("{0}", e.ToString());

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
            (*--it)->OnEvent(e);
            if (e.Handle)
                break;
        }
    }

    void Application::Run()
    {
        while (m_Running) {
            // glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            // glClear(GL_COLOR_BUFFER_BIT);

            m_BlueShader->Bind();
            m_SquareVA->Bind();
            glDrawElements(GL_TRIANGLES, m_SquareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_Shader->Bind();
            m_VertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowCloseEvent(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResizeEvent(WindowResizeEvent& event)
    {
        // m_Running = false;
        HZ_CORE_INFO("width: {0}, height: {1}", event.GetWidth(), event.GetHeight());
        return true;
    }
} // namespace Hazel
