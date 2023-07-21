#include "Core/Application.h"

Dizzy::Application* CreateApplication(const Dizzy::ApplicationArgs& args)
{
	return new Dizzy::Application(args);
}

int main(int argc, const char** argv)
{
	Dizzy::Logger::Init();

	Dizzy::ApplicationArgs args;
	args.name = "Dizzy";
	args.runtimePath = std::filesystem::current_path();

	Dizzy::Application* app = CreateApplication(args);
	app->Run();
}