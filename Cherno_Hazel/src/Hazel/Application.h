#pragma once

#include "core.h"
#include "Window.h"

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

		bool OnWindowCloseEvent(WindowCloseEvent& event);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
