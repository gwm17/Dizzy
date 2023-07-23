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

		DZ_INFO("Creating a window...");
		m_window = Window::Create();
		m_window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatch(e);
		dispatch.Dispatch<WindowClosedEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClosedEvent));
		for (auto iter = m_layerStack.end(); iter != m_layerStack.begin(); )
		{
			(*(--iter))->OnEvent(e);
			if (e.m_isHandled)
				break;
		}
	}

	bool Application::OnWindowClosedEvent(WindowClosedEvent& e)
	{
		DZ_INFO("Dizzy recieved a WindowClosedEvent!");
		Stop();
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Run()
	{
		while (m_isRunning)
		{
			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_window->OnUpdate();
		}
	}
}