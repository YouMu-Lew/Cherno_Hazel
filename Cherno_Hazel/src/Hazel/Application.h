#pragma once

#include "core.h"
#include "Window.h"

#include "Hazel\LayerStack.h"
#include "Hazel\ImGui\ImGuiLayer.h"

#include "Events\Event.h"
#include "Events\ApplicationEvent.h"

namespace Hazel {

	class HAZEL_API Application
	{
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

		std::unique_ptr<Hazel::Window> m_Window;
		Hazel::ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		Hazel::LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
