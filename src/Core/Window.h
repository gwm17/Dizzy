#pragma once

#include "DZCore.h"
#include "Events/Event.h"

class GLFWwindow;

namespace Dizzy {

	//Default properties
	struct WindowProperties
	{
		uint32_t width = 1280;
		uint32_t height = 720;
		std::string name = "Dizzy";
	};

	class Window
	{
	using EventFunc = std::function<void(Event&)>;
	public:
		Window(const WindowProperties& props);
		~Window();

		void OnUpdate();
		uint32_t GetWidth() const { return m_data.width; }
		uint32_t GetHeight() const { return m_data.height; }
		const std::string& GetName() const { return m_data.name; }

		void SetEventCallback(const EventFunc& f) { m_data.eventCallback = f; }

		void SetVsync(bool isVsync);
		bool IsVsync() const { return m_data.isVsync; }
		void* GetNativeWindow() const { return m_window; }

		//For ease of use
		static Window* Create(const WindowProperties& props = WindowProperties()) { return new Window(props); }
	private:
		void Init(const WindowProperties& props);
		void Shutdown();

		struct WindowData
		{
			int width;
			int height;
			std::string name;
			bool isVsync;
			EventFunc eventCallback;
		};

		WindowData m_data;
		GLFWwindow* m_window;
	};
}