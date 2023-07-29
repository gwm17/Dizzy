#include "OpenGLAPI.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Dizzy {

	void OpenGLAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color[0], color[1], color[2], color[3]);
	}

	float OpenGLAPI::GetFrameTime()
	{
		return glfwGetTime();
	}
}