#pragma once

#include "Hazel\Window.h"
// 如果未定义 GLFW_INCLUDE_NONE
// 确保先 include glad.h 之后再 include glfw3.h
// 否则会报错 C1189 #error: OpenGL header already included, remove this include, glad already provides it
#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace Hazel {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		virtual void* GetNativeWindow() const override { return m_Window; }

	private:
		GLFWwindow* m_Window;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		void Init(const WindowProps& props);
		void Shutdown();
	};

}