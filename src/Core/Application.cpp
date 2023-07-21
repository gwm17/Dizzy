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
		}
	}
}