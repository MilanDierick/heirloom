// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_LOG_H
#define HEIRLOOM_LOG_H

#include <spdlog/spdlog.h>

namespace Heirloom
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger();
		static std::shared_ptr<spdlog::logger>& GetClientLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

template <typename ... Params>
constexpr static void CoreTrace(Params... parameters)
{
	Heirloom::Log::GetCoreLogger()->trace(parameters...);
}

// Core log macros
#define HL_CORE_TRACE(...) 	::Heirloom::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HL_CORE_INFO(...) 	::Heirloom::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HL_CORE_WARN(...) 	::Heirloom::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HL_CORE_ERROR(...) 	::Heirloom::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HL_CORE_FATAL(...) 	::Heirloom::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HL_TRACE(...) 		::Heirloom::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HL_INFO(...) 		::Heirloom::Log::GetClientLogger()->info(__VA_ARGS__)
#define HL_WARN(...) 		::Heirloom::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HL_ERROR(...) 		::Heirloom::Log::GetClientLogger()->error(__VA_ARGS__)
#define HL_FATAL(...) 		::Heirloom::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif //HEIRLOOM_LOG_H
