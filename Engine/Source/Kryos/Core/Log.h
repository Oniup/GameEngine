#pragma once

#include "Kryos/Core/ApplicationModule.h"
#include <fmt/color.h>
#include <string>
#include <string_view>
#include <vector>

namespace Kryos
{

	enum LogOutputSeverity
	{
		LogOutput_Undefined		= 0,
		LogOutput_Trace			= 1 << 0,
		LogOutput_VerboseInfo	= 1 << 1,
		LogOutput_Info			= 1 << 2,
		LogOutput_Warning		= 1 << 3,
		LogOutput_Error			= 1 << 4,
		LogOutput_Fatal			= 1 << 5,
	};

	struct LogEntry
	{
		const std::string Message;
		const std::string_view File;
		const std::string_view Function;
		LogOutputSeverity Severity;
		int Line;

		const std::string_view SeverityToString() const;
		const fmt::color SeverityToColor() const;
	};

	class LogOutput
	{
	public:
		LogOutput(int severityFilter = LogOutput_Trace | LogOutput_VerboseInfo);
		virtual ~LogOutput() = default;

		virtual void Print(const LogEntry& entry) = 0;

	protected:
		int m_Severity;
	};

	class TerminalLogOutput : public LogOutput
	{
	public:
		TerminalLogOutput(int severityFilter = LogOutput_Trace | LogOutput_VerboseInfo);
		~TerminalLogOutput() override = default;

		void Print(const LogEntry& entry) override;
	};

	class FileLogOutput : public LogOutput
	{
	public:
		FileLogOutput(const std::string& outputPath, int severityFilter = LogOutput_Trace | LogOutput_VerboseInfo);
		~FileLogOutput() override = default;

		void Print(const LogEntry& entry) override;

	private:
		std::string m_OutputPath;
	};

	class Log : public ApplicationModule
	{
	public:
		Log() = default;
		~Log() override;

		static void PushOutput(LogOutput* output);
		static void PrintToAllOutputs(const LogEntry& entry);

	private:
		std::vector<LogOutput*> m_Outputs;
	};

}
