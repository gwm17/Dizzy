#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Dizzy {

	class Logger
	{
	public:
	
		static void Init();

		static std::shared_ptr<spdlog::logger> GetLogger() { return s_logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_logger;
	};
}

//Macros for clean code. Different logging levels.
#define DZ_CRITICAL(...) ::Dizzy::Logger::GetLogger()->critical(__VA_ARGS__)
#define DZ_WARN(...) ::Dizzy::Logger::GetLogger()->warn(__VA_ARGS__)
#define DZ_ERROR(...) ::Dizzy::Logger::GetLogger()->error(__VA_ARGS__)
#define DZ_TRACE(...) ::Dizzy::Logger::GetLogger()->trace(__VA_ARGS__)
#define DZ_INFO(...) ::Dizzy::Logger::GetLogger()->info(__VA_ARGS__)