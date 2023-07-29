#pragma once

#include "DZCore.h"
#include "Events/Event.h"
#include "glm/glm.hpp"

struct GLFWwindow;

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
	public:
		using EventFunc = std::function<void(Event&)>;
		virtual ~Window() {};

		virtual void OnUpdate() = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual const std::string& GetName() const = 0;

		virtual glm::vec2 GetFrameBufferSize() = 0;

		virtual void SetEventCallback(const EventFunc& f) = 0;

		virtual void SetVsync(bool isVsync) = 0;
		virtual bool IsVsync() const = 0;
		virtual void* GetNativeWindow() = 0;

		//For ease of use
		static Window* Create(const WindowProperties& props = WindowProperties());
	};
}