#include "hzpch.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

export module OpenGLContext;

import GraphicsContext;

export namespace Hazel {

    class OpenGLContext : public GraphicsContext {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_windowHandle;
    };

} // namespace Hazel

/**
 * Implementation
 */

namespace Hazel {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle) {}

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_windowHandle);

        /** glfwGetProcAddress 是 GLFW 提供的函数，用于获取 OpenGL 函数的地址。通过将(GLADloadproc)glfwGetProcAddress
         * 传递给 gladLoadGLLoader，GLAD 可以加载所有必要的 OpenGL 函数 */
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        HZ_CORE_ASSERT(status, "Failed to initialize glad!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_windowHandle);
    }
} // namespace Hazel
