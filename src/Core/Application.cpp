#include "Application.h"

namespace Dizzy {

	Application* Application::s_appInstance = nullptr;

	Application::Application(const ApplicationArgs& args):
		m_args(args), m_isRunning(true)
	{
		if (s_appInstance == nullptr)
		{
			s_appInstance = this;
		}

		DZ_INFO("Dizzy has been created!");

		m_layerStack.PushLayer(new Layer("TestLayer"));
	}

	Application::~Application()
	{
	}

	void Application::Close()
	{
	}

	void Application::OnEvent()
	{
	}

	void Application::PushLayer()
	{
	}

	void Application::PushOverlay()
	{
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			for (Layer* layer : m_layerStack)
				DZ_INFO("Found Layer: {}", layer->GetName());
		}
	}
}