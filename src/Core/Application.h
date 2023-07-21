#pragma once

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
		void Close();

		void OnEvent();
		void PushLayer();
		void PushOverlay();

		const ApplicationArgs& GetArgs() { return m_args; }

		static Application* GetInstance() { return s_appInstance; }

	private:
		ApplicationArgs m_args;
		bool m_isRunning;

		static Application* s_appInstance;
	};
}