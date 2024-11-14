#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include <fmt/color.h>
#include <string>
#include <string_view>
#include <vector>

#define KY_LOG_OUTPUT_DEFAULT_SEVERITY_FILTER Kryos::LogSeverity_Trace | Kryos::LogSeverity_Verbose

namespace Kryos
{

	using LogOutputSeverityFlags = int;
	enum LogOutputSeverity
	{
		LogSeverity_None		= 0,
		LogSeverity_Trace		= 1 << 0,
		LogSeverity_Verbose		= 1 << 1,
		LogSeverity_Info		= 1 << 2,
		LogSeverity_Warning		= 1 << 3,
		LogSeverity_Error		= 1 << 4,
		LogSeverity_Fatal		= 1 << 5,
	};

	struct LogEntry
	{
		const std::string Message;
		const std::string_view File;
		const std::string_view Function;
		LogOutputSeverity Severity;
		int Line;

		const std::string_view SeverityToString() const;
	};

	class LogOutput
	{
	public:
		LogOutput(LogOutputSeverityFlags severityFilter = KY_LOG_OUTPUT_DEFAULT_SEVERITY_FILTER);
		virtual ~LogOutput() = default;

		virtual void Print(const LogEntry& entry) = 0;

	protected:
		int m_Severity;
	};

	class TerminalLogOutput final : public LogOutput
	{
	public:
		TerminalLogOutput(LogOutputSeverityFlags severityFilter = KY_LOG_OUTPUT_DEFAULT_SEVERITY_FILTER);
		~TerminalLogOutput() override = default;

		void Print(const LogEntry& entry) override;

	private:
		static const fmt::text_style SeverityFormatStyle(const LogEntry& entry);
	};

	class FileLogOutput final : public LogOutput
	{
	public:
		FileLogOutput(const std::string& outputPath, LogOutputSeverityFlags severityFilter = KY_LOG_OUTPUT_DEFAULT_SEVERITY_FILTER);
		~FileLogOutput() override = default;

		void Print(const LogEntry& entry) override;

	private:
		std::string m_OutputPath;
	};

	class Log final : public ApplicationModule
	{
	public:
		Log();
		~Log() override;

		static void PushOutput(LogOutput* output);
		static void PrintToAllOutputs(const LogEntry& entry);

	private:
		std::vector<LogOutput*> m_Outputs;

		static Log* s_Instance;
	};

}

#define KY_INTERNAL_LOG_MESSAGE(_Severity, ...)			\
	Kryos::Log::PrintToAllOutputs(						\
		Kryos::LogEntry{								\
			.Message = fmt::format(__VA_ARGS__),		\
			.File = __FILE__,							\
			.Function = __FUNCTION__,					\
			.Severity = Kryos::LogSeverity_##_Severity,	\
			.Line = __LINE__,							\
		}												\
	)

#if (defined(KY_DEBUG) || defined(KY_RELEASE)) || (defined(KY_STILL_USE_LOG) && defined(KY_DIST)) 
#	ifndef KY_DISABLE_DEBUG_INFO_LOGS
#		define KY_TRACE(...) KY_INTERNAL_LOG_MESSAGE(Trace, __VA_ARGS__)
#		define KY_VERBOSE(...) KY_INTERNAL_LOG_MESSAGE(Verbose, __VA_ARGS__)
#		define KY_INFO(...) KY_INTERNAL_LOG_MESSAGE(Info, __VA_ARGS__)
#	else
#		define KY_TRACE(...)
#		define KY_VERBOSE(...)
#		define KY_INFO(...)
#	endif

#	define KY_WARNING(...) KY_INTERNAL_LOG_MESSAGE(Warning, __VA_ARGS__)
#	define KY_ERROR(...) KY_INTERNAL_LOG_MESSAGE(Error, __VA_ARGS__)
#	define KY_FATAL(...) KY_INTERNAL_LOG_MESSAGE(Fatal, __VA_ARGS__)
#else
#	define KY_TRACE(...)
#	define KY_VERBOSE(...)
#	define KY_INFO(...)
#	define KY_WARNING(...)
#	define KY_ERROR(...)
#	define KY_FATAL(...)
#endif
