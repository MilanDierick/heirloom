// Author: Milan Dierick
// Solution: Heirloom

#include "hlpch.h"
#include "Instrumentation.h"

namespace Heirloom
{
	Instrumentation::Instrumentation()
			: m_CurrentSession(nullptr)
	{
	}

	void Instrumentation::BeginSession(const std::string& name, const std::string& filepath)
	{
		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession)
		{
			// If there is already a current session, then close it before beginning new one.
			// Subsequent profiling output meant for the original session will end up in the
			// newly opened session instead.  That's better than having badly formatted
			// profiling output.
			if (Log::GetCoreLogger())
			{
				// Edge case: BeginSession() might be before Log::Init()
				HL_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.",
						name.c_str(),
						m_CurrentSession->Name.c_str());
			}

			InternalEndSession();
		}

		m_OutputStream.open(filepath);

		if (m_OutputStream.is_open())
		{
			m_CurrentSession = new InstrumentationSession({name});
			WriteHeader();
		}

		else
		{
			if (Log::GetCoreLogger())
			{
				// Edge case: BeginSession() might be before Log::Init()
				HL_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath.c_str());
			}
		}
	}

	void Instrumentation::EndSession()
	{
		std::lock_guard lock(m_Mutex);
		InternalEndSession();
	}

	void Instrumentation::WriteProfile(const ProfileResult& result)
	{
		std::stringstream json;

		std::string name = result.Name;
		std::ranges::replace(name, '"', '\'');

		json << std::setprecision(3) << std::fixed;
		json << ",{";
		json << "\"cat\":\"function\",";
		json << "\"dur\":" << result.ElapsedTime.count() << ',';
		json << "\"name\":\"" << name << "\",";
		json << "\"ph\":\"X\",";
		json << "\"pid\":0,";
		json << "\"tid\":" << result.ThreadID << ",";
		json << "\"ts\":" << result.Start.count();
		json << "}";

		std::lock_guard lock(m_Mutex);
		if (m_CurrentSession)
		{
			m_OutputStream << json.str();
			m_OutputStream.flush();
		}
	}

	Instrumentation& Instrumentation::Get()
	{
		static Instrumentation instance;
		return instance;
	}

	void Instrumentation::WriteHeader()
	{
		m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
		m_OutputStream.flush();
	}

	void Instrumentation::WriteFooter()
	{
		m_OutputStream << "]}";
		m_OutputStream.flush();
	}

	void Instrumentation::InternalEndSession()
	{
		if (m_CurrentSession)
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
		}
	}

	InstrumentationTimer::InstrumentationTimer(const char* name)
			: m_Name(name),
			  m_Stopped(false)
	{
		m_StartTimePoint = std::chrono::steady_clock::now();
	}

	InstrumentationTimer::~InstrumentationTimer()
	{
		if (!m_Stopped)
		{
			Stop();
		}
	}

	void InstrumentationTimer::Stop()
	{
		const auto endTimePoint = std::chrono::steady_clock::now();

		const auto highResStart = FloatingPointMicroseconds{m_StartTimePoint.time_since_epoch()};
		const auto elapsedTime  = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).
				time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).
				time_since_epoch();

		Instrumentation::Get().WriteProfile({m_Name, highResStart, elapsedTime, std::this_thread::get_id()});

		m_Stopped = true;
	}
}