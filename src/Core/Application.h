#pragma once

#include "DZCore.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"

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

		static Application* GetInstance() { return s_appInstance; }

	private:
		bool OnWindowClosedEvent(WindowClosedEvent& e);

		ApplicationArgs m_args;
		bool m_isRunning;

		LayerStack m_layerStack;

		static Application* s_appInstance;
	};
}