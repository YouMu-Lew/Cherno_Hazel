#pragma once

#include "Hazel\Renderer\GraphicsContext.h"
#include "Platform\OpenGL\OpenGLContext.h"

#include <GLFW\glfw3.h>

import Window;

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
        GraphicsContext* m_context;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;

        void Init(const WindowProps& props);
        void Shutdown();
    };

} // namespace Hazel
