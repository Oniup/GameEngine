#include "Kryos/Core/Defines.h"
#include "Kryos/Core/Log.h"
#include <filesystem>
#include <fmt/format.h>

namespace Kryos
{

	const std::string_view LogEntry::SeverityToString() const
	{
		switch (Severity)
		{
		case LogOutput_Trace:		return "Trace";
		case LogOutput_VerboseInfo: return "Verbose";
		case LogOutput_Info:		return "Info";
		case LogOutput_Warning:		return "Warning";
		case LogOutput_Error:		return "Error";
		case LogOutput_Fatal:		return "Fatal";
		default:					return "Unknown";
		}
	}

	const fmt::color LogEntry::SeverityToColor() const 
	{
		switch (Severity)
		{
		case LogOutput_Trace:		return fmt::color::gray;
		case LogOutput_VerboseInfo: return fmt::color::dark_gray;
		case LogOutput_Info:		return fmt::color::white;
		case LogOutput_Warning:		return fmt::color::light_golden_rod_yellow;
		case LogOutput_Error:		return fmt::color::indian_red;
		case LogOutput_Fatal:		return fmt::color::indian_red;
		default:					return fmt::color::white;
		}
	}

	LogOutput::LogOutput(int severityFilter /*= LogOutput_Trace | LogOutput_VerboseInfo*/)
		: m_Severity((LogOutput_Trace | LogOutput_VerboseInfo | LogOutput_Info | LogOutput_Warning | LogOutput_Error | LogOutput_Fatal) & ~severityFilter)
	{
	}

	TerminalLogOutput::TerminalLogOutput(int severityFilter /*= LogOutput_Trace | LogOutput_VerboseInfo*/)
		: LogOutput(severityFilter) 
	{
	}
	
	void TerminalLogOutput::Print(const LogEntry& entry)
	{
		std::FILE* file;
		if (entry.Severity > LogOutput_Warning)
			file = stderr;
		else
			file = stdout;

		fmt::print(file, fmt::emphasis::italic | fg(entry.SeverityToColor()), "[{} {}:{}:{}]: {}\n",
			entry.SeverityToString(), std::filesystem::path(entry.File).string(), entry.Function, entry.Line, entry.Message);
	}

	FileLogOutput::FileLogOutput(const std::string& outputPath, int severityFilter /*= LogOutput_Trace | LogOutput_VerboseInfo*/)
		: LogOutput(severityFilter), m_OutputPath(outputPath)
	{
		KY_ASSERT(!m_OutputPath.empty(), "A file output requires a path to dump logs");
	}

	void FileLogOutput::Print(const LogEntry& entry)
	{
		std::FILE* file = std::fopen(m_OutputPath.c_str(), "a");

		fmt::print(file, fmt::emphasis::italic | fg(entry.SeverityToColor()), "[{} {}:{}:{}]: {}\n",
			entry.SeverityToString(), std::filesystem::path(entry.File).string(), entry.Function, entry.Line, entry.Message);
	}

	Log::~Log()
	{
		for (LogOutput* output : m_Outputs)
			delete output;
	}

	void Log::PushOutput(LogOutput* output)
	{
	}

	void Log::PrintToAllOutputs(const LogEntry& entry)
	{

	}

	void Log::ImplPushOutput(LogOutput* output)
	{
		KY_ASSERT(output, "Log output is nullptr");
		m_Outputs.push_back(output);
	}

	void Log::ImplPrintToAllOutputs(const LogEntry& entry)
	{
		for (LogOutput* output : m_Outputs)
			output->Print(entry);
	}

}

