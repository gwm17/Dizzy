#include "OpenGLContext.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Dizzy {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
		m_windowHandle(windowHandle)
	{
	}

	OpenGLContext::~OpenGLContext()
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		//Report graphics status
		DZ_INFO("Loaded OpenGL with glad Init status {0}", status);
		DZ_INFO("Loaded OpenGL renderer");
		DZ_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		DZ_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		DZ_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}
}