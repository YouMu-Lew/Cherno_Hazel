#include "hzpch.h"

#include "OpenGLContext.h"

#include <glad\glad.h>

namespace Hazel {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_windowHandle(windowHandle) {

	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_windowHandle);

		/** glfwGetProcAddress 是 GLFW 提供的函数，用于获取 OpenGL 函数的地址。通过将(GLADloadproc)glfwGetProcAddress 传递给 gladLoadGLLoader，GLAD 可以加载所有必要的 OpenGL 函数 */
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		HZ_CORE_ASSERT(status, "Failed to initialize glad!");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}
