#include "Window.h"
#include "GLFW/glfw3.h"
#include "Events/KeyEvent.h"
#include "Events/AppEvent.h"
#include "Events/MouseEvent.h"

namespace Dizzy {

	Window::Window(const WindowProperties& props)
	{
		Init(props);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Init(const WindowProperties& props)
	{
		glfwSetErrorCallback([](int error, const char* description) {
			DZ_ERROR("GLFW ErrorCode: {} Description: {}", error, description);
		});

		DZ_INFO("Creating a window with height: {} width: {}", props.height, props.width);

		m_data.width = props.width;
		m_data.height = props.height;
		m_data.name = props.name;
		m_data.isVsync = true;

		if (!glfwInit())
		{
			DZ_ERROR("Unable to initialize GLFW!");
			return;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.name.c_str(), nullptr, nullptr);
		if (!glfwVulkanSupported())
		{
			DZ_ERROR("Linked GLFW does not support Vulkan!");
			return;
		}

		glfwSetWindowUserPointer(m_window, &m_data);

		std::vector<const char*> requiredExtensions;
		uint32_t extensionCount = 0;
		const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);
		for (uint32_t i = 0; i < extensionCount; i++)
		{
			requiredExtensions.push_back(extensions[i]);
		}

		//Vulkan init here
		//m_vulkanContext = VulkanContext::Init(requiredExtensions);
		//Or something

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*) glfwGetWindowUserPointer(window); //Icky casting
			data.width = width;
			data.height = height;
			WindowResizedEvent e(width, height);
			data.eventCallback(e);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowClosedEvent e;
			data.eventCallback(e);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.eventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.eventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					//GLFW doesnt have a hold count, so here we just pass 1 to indicate a hold is happening.
					KeyPressedEvent e(key, 1);
					data.eventCallback(e);
					break;
				}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int character)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent e(character);
				data.eventCallback(e);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.eventCallback(e);
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.eventCallback(e);
				}
				}
			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent e((float)xoffset, (float)yoffset);
				data.eventCallback(e);
			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent e((float)xpos, (float)ypos);
				data.eventCallback(e);
			});
		
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_window);
		//Presumably some vulkan nonsense here too
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		//Some vulkan stuff
	}

	void Window::SetVsync(bool isVsync)
	{
		m_data.isVsync = isVsync;
		//Presumably some vulkan stuff
	}
}