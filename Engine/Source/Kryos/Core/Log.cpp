#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Application.h"
#include "Kryos/Core/Log.h"
#include <filesystem>
#include <fmt/format.h>

namespace Kryos
{

	Kryos::Log* Log::s_Instance = nullptr;

	const std::string_view LogEntry::SeverityToString() const
	{
		switch (Severity)
		{
		case LogSeverity_Trace:		return "Trace";
		case LogSeverity_Verbose:	return "Verbose";
		case LogSeverity_Info:		return "Info";
		case LogSeverity_Warning:	return "Warning";
		case LogSeverity_Error:		return "Error";
		case LogSeverity_Fatal:		return "Fatal";
		default:					return "Unknown";
		}
	}

	LogOutput::LogOutput(LogOutputSeverityFlags severityFilter /*= LogOutput_Trace | LogOutput_VerboseInfo*/)
		: m_Severity((LogSeverity_Trace | LogSeverity_Verbose | LogSeverity_Info | LogSeverity_Warning | LogSeverity_Error | LogSeverity_Fatal) & ~severityFilter)
	{
	}

	TerminalLogOutput::TerminalLogOutput(LogOutputSeverityFlags severityFilter /*= LogOutput_Trace | LogOutput_VerboseInfo*/)
		: LogOutput(severityFilter) 
	{
	}
	
	void TerminalLogOutput::Print(const LogEntry& entry)
	{
		if (m_Severity & entry.Severity)
		{
			std::FILE* file;
			if (entry.Severity > LogSeverity_Warning)
				file = stderr;
			else
				file = stdout;

			fmt::print(file, SeverityFormatStyle(entry), "[{} {}-{}:{}]: {}\n", entry.SeverityToString(), 
				std::filesystem::path(entry.File).filename().string(), entry.Function, entry.Line, entry.Message);
			std::fflush(file);
		}
	}

	const fmt::text_style TerminalLogOutput::SeverityFormatStyle(const LogEntry& entry)
	{
		switch (entry.Severity)
		{
		case LogSeverity_Trace:		return fmt::emphasis::italic | fmt::fg(fmt::rgb(KY_COLOR_RGB_DARKER_GREY));
		case LogSeverity_Verbose:	return fmt::emphasis::italic | fmt::fg(fmt::rgb(KY_COLOR_RGB_DARKER_GREY));
		case LogSeverity_Info:		return fmt::fg(fmt::rgb(KY_COLOR_RGB_GREY));
		case LogSeverity_Warning:	return fmt::fg(fmt::rgb(KY_COLOR_RGB_ORANGE_YELLOW));
		case LogSeverity_Error:		return fmt::fg(fmt::rgb(KY_COLOR_RGB_RED));
		case LogSeverity_Fatal:		return fmt::emphasis::bold | fmt::fg(fmt::rgb(KY_COLOR_RGB_DEEP_RED));
		default:					return fmt::fg(fmt::rgb(KY_COLOR_RGB_GREY));
		}
	}

	FileLogOutput::FileLogOutput(const std::string& outputPath, LogOutputSeverityFlags severityFilter /*= LogOutput_Trace | LogOutput_VerboseInfo*/)
		: LogOutput(severityFilter), m_OutputPath(outputPath)
	{
		KY_ASSERT(!m_OutputPath.empty(), "A file output requires a path to dump logs");
	}

	void FileLogOutput::Print(const LogEntry& entry)
	{
		std::FILE* file = std::fopen(m_OutputPath.c_str(), "a");

		fmt::print(file, "[{} {}:{}:{}]: {}\n",
			entry.SeverityToString(), std::filesystem::path(entry.File).filename().string(), entry.Function, entry.Line, entry.Message);
	}

	Log::Log()
	{
		s_Instance = this;
	}

	Log::~Log()
	{
		for (LogOutput* output : m_Outputs)
			delete output;
		s_Instance = nullptr;
	}

	void Log::PushOutput(LogOutput* output)
	{
		KY_ASSERT(output, "Log output is nullptr");
		s_Instance->m_Outputs.push_back(output);
	}

	void Log::PrintToAllOutputs(const LogEntry& entry)
	{
		if (s_Instance)
		{
			for (LogOutput* output : s_Instance->m_Outputs)
				output->Print(entry);
		}
	}

}

