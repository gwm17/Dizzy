#include "OpenGLWindow.h"
#include "glad/glad.h"
#include "OpenGLContext.h"
#include "Events/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Dizzy {

	bool OpenGLWindow::s_glfwInitialized = false;

	//This function can be defined EXACTLY once in a project
	Window* Window::Create(const WindowProperties& props)
	{
		return new OpenGLWindow(props);
	}

	static void GLFWErrorCallback(int error, const char* description)
	{
		DZ_ERROR("GLFW error: code[{}] description -- {}", error, description);
	}

	OpenGLWindow::OpenGLWindow(const WindowProperties& props)
	{
		Init(props);
	}

	OpenGLWindow::~OpenGLWindow()
	{
		Shutdown();
	}

	void OpenGLWindow::OnUpdate()
	{
		glfwPollEvents();
		m_context->SwapBuffers();
	}

	glm::vec2 OpenGLWindow::GetFrameBufferSize()
	{
		int w, h;
		glfwGetFramebufferSize(m_windowHandle, &w, &h);
		return glm::vec2(w, h);
	}

	void OpenGLWindow::Init(const WindowProperties& props)
	{
		m_windowData.width = props.width;
		m_windowData.height = props.height;
		m_windowData.name = props.name;

		DZ_INFO("Creating OpenGL window with name: {} and width: {} and height: {}", props.name, props.width, props.height);

		if (!s_glfwInitialized)
		{
			int result = glfwInit();
			DZ_INFO("GLFW initalized with status {}", result);
			glfwSetErrorCallback(GLFWErrorCallback);
		}
		//Apple specific. OpenGL is technically deprecated, so a little extra work to force the correct version
		#ifdef __APPLE__
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
		#endif

		m_windowHandle = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.name.c_str(), nullptr, nullptr);
		m_context = new OpenGLContext(m_windowHandle);
		m_context->Init();
		SetVsync(true);

		glfwSetWindowUserPointer(m_windowHandle, &m_windowData);

		//Set all of the callback functions for the window. 
		glfwSetWindowSizeCallback(m_windowHandle, [](GLFWwindow* window, int width, int height)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;
				WindowResizedEvent event(width, height);
				data.eventCallback(event);
			});

		glfwSetWindowCloseCallback(m_windowHandle, [](GLFWwindow* window)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				WindowClosedEvent event;
				data.eventCallback(event);
			});

		glfwSetKeyCallback(m_windowHandle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					//GLFW doesnt have a hold count, so here we just pass 1 to indicate a hold is happening.
					KeyPressedEvent event(key, 1);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_windowHandle, [](GLFWwindow* window, unsigned int character)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(character);
				data.eventCallback(event);
			});

		glfwSetMouseButtonCallback(m_windowHandle, [](GLFWwindow* window, int button, int action, int mods)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.eventCallback(event);
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.eventCallback(event);
				}
				}
			});

		glfwSetScrollCallback(m_windowHandle, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xoffset, (float)yoffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(m_windowHandle, [](GLFWwindow* window, double xpos, double ypos)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xpos, (float)ypos);
				data.eventCallback(event);
			});
	}

	void OpenGLWindow::Shutdown()
	{
		glfwDestroyWindow(m_windowHandle);
	}
}