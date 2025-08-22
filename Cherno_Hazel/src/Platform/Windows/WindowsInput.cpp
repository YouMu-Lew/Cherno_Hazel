#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel\Application.h"
#include <GLFW\glfw3.h>

namespace Hazel {

    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int keycode)
    {
        Application& app = Application::Get();
        Window& window = app.GetWindow();
        GLFWwindow* g_window = static_cast<GLFWwindow*>(window.GetNativeWindow());
        const auto state = glfwGetKey(g_window, keycode);
        return state != GLFW_RELEASE;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int button)
    {
        const auto state =
            glfwGetMouseButton(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow()), button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        auto g_window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(g_window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto [x, _] = GetMousePositionImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto [_, y] = GetMousePositionImpl();
        return y;
    }

} // namespace Hazel
