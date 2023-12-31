#pragma once

#include "DZCore.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"
#include "ImGuiLayer.h"
#include "glm/glm.hpp"

namespace Dizzy {

	//Arguments for initializing the application
	struct ApplicationArgs
	{
		std::string name = "";
		std::filesystem::path runtimePath = "";
	};

	class Application
	{
	public:
		Application(const ApplicationArgs& args);
		~Application();

		void Run();
		void Stop() { m_isRunning = false; }

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		const ApplicationArgs& GetArgs() { return m_args; }

		static Application& GetInstance() { return *s_appInstance; }

		Window& GetWindow() { return *m_window; }

	private:
		bool OnWindowClosedEvent(WindowClosedEvent& e);

		ApplicationArgs m_args;
		bool m_isRunning;

		std::unique_ptr<Window> m_window;
		LayerStack m_layerStack;
		ImGuiLayer* m_imguiLayer;

		glm::vec4 m_clearColor;

		static Application* s_appInstance;
	};
}