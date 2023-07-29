#pragma once

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Dizzy {

	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(const WindowProperties& props);
		virtual ~OpenGLWindow();

		virtual void OnUpdate() override;
		virtual uint32_t GetWidth() const override { return m_windowData.width; }
		virtual uint32_t GetHeight() const override { return m_windowData.height; }
		virtual const std::string& GetName() const override { return m_windowData.name; }

		virtual glm::vec2 GetFrameBufferSize() override;

		virtual void SetEventCallback(const Window::EventFunc& f) override { m_windowData.eventCallback = f; }

		virtual void SetVsync(bool isVsync) override { m_windowData.isVsync = isVsync; }
		virtual bool IsVsync() const override { return m_windowData.isVsync; }
		virtual void* GetNativeWindow() override { return m_windowHandle; }

	private:
		struct Data
		{
			Window::EventFunc eventCallback;
			int width;
			int height;
			std::string name;
			bool isVsync;
		};

		void Init(const WindowProperties& props);
		void Shutdown();

		static bool s_glfwInitialized;
		GLFWwindow* m_windowHandle;
		GraphicsContext* m_context;

		Data m_windowData;
	};
}