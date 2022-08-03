// Author: Milan Dierick
// Solution: Heirloom

#ifndef HEIRLOOM_INSTRUMENTATION_H
#define HEIRLOOM_INSTRUMENTATION_H

#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>

namespace Heirloom
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfileResult
	{
		std::string Name;
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct InstrumentationSession
	{
		std::string Name;
	};

	class Instrumentation
	{
	public:
		Instrumentation();

		void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		void EndSession();
		void WriteProfile(const ProfileResult& result);

		static Instrumentation& Get();

	private:
		void WriteHeader();
		void WriteFooter();
		void InternalEndSession();

		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
//		[[maybe_unused]] int m_ProfileCount;
	};

	class InstrumentationTimer
	{
	public:
		explicit InstrumentationTimer(const char* name);

		~InstrumentationTimer();

		void Stop();
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimePoint;
		bool m_Stopped;
	};

#define TOKENPASTE(x, y) x ## y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)

#if HL_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
	#define HL_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
	#define HL_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__FUNCSIG__)
	#define HL_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
	#define HL_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
	#define HL_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
	#define HL_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
	#define HL_FUNC_SIG __func__
	#else
	#define HL_FUNC_SIG "HL_FUNC_SIG unknown!"
	#endif
	#define HL_PROFILE_BEGIN_SESSION(name, filepath) ::Heirloom::Instrumentation::Get().BeginSession(name, filepath)
	#define HL_PROFILE_END_SESSION() ::Heirloom::Instrumentation::Get().EndSession()
	#define HL_PROFILE_SCOPE(name) ::Heirloom::InstrumentationTimer TOKENPASTE2(timer, __LINE__)(name);
	#define HL_PROFILE_FUNCTION() HL_PROFILE_SCOPE(HL_FUNC_SIG)
#else
#define HL_PROFILE_BEGIN_SESSION(name, filepath);
#define HL_PROFILE_END_SESSION();
#define HL_PROFILE_SCOPE(name);
#define HL_PROFILE_FUNCTION();
#endif
}

#endif //HEIRLOOM_INSTRUMENTATION_H
