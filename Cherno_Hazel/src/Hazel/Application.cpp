#include "hzpch.h"
#include "Application.h"

// 如果定义了 GLFW_INCLUDE_NONE
// 此处需要修改为 include <glad\glad.h>
// #include <GLFW\glfw3.h>
#include <glad\glad.h>

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

		// 生成一个顶点数组对象（VAO），用于保存顶点数据和属性配置的状态
		glGenVertexArrays(1, &m_VertexArray);
		// 绑定VAO，使其成为当前活动的顶点数组对象
		glBindVertexArray(m_VertexArray);

		// 定义一个包含3个顶点的数组，每个顶点有3个浮点数（x, y, z坐标）
        float vertices[3 * 3] = {
            -1.0f, -1.0f, 0.0f, // 第一个顶点
            -1.0f, 1.0f,  0.0f, // 第二个顶点
            1.0f,  1.0f,  0.0f, // 第三个顶点
        };

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        // 定义一个包含3个索引的数组，用于指定顶点的绘制顺序
		uint32_t indices[3] = { 0, 1, 2 };

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

		// 启用顶点属性索引0，表示该属性将被传递给着色器
		glEnableVertexAttribArray(0);
		// 配置顶点属性指针，定义如何从VBO中读取顶点数据：
		// - 索引为0
		// - 每个顶点包含3个分量（x, y, z）
		// - 数据类型为GL_FLOAT
		// - 不进行归一化处理（GL_FALSE）
		// - 顶点之间的步长为3 * sizeof(float)
		// - 数据偏移量为nullptr（从缓冲区的起始位置开始）
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

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
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
			//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexBuffer->Bind();
			m_IndexBuffer->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
        HZ_CORE_INFO("width: {0}, height: {1}",event.GetWidth(), event.GetHeight());
        return true;
    }
}
