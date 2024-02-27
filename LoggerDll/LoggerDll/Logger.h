#pragma once
#include "export.h"

#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <source_location>
#include <string>
#include <thread>

namespace KOD {

static std::recursive_mutex m_mutex;

class Logger
{
public:
	enum class ThreadState
	{
		RUNNING,
		STOPPED
	};

	enum class LogSeverity
	{
		DEBUG = 0,
		INFO = 1,
		WARNING = 2,
		ERROR = 3,
		FATAL = 4,
		INTERNAL = 99,
	};

	LOGGER_DLL Logger();
	LOGGER_DLL ~Logger();
	LOGGER_DLL void log(KOD::Logger::LogSeverity lvl, const char* message,
	                    const std::source_location loc = std::source_location::current());

	LOGGER_DLL void setLogLevel(KOD::Logger::LogSeverity lvl);
	LOGGER_DLL void setFileNameMaxLenght(size_t fileNameMaxCharacter);

	LOGGER_DLL void join();
	LOGGER_DLL void stop();

private:
	void logHandler();
	void internalLog(const char* message, const std::source_location loc = std::source_location::current());
	std::string getSeverityString(KOD::Logger::LogSeverity lvl);
	std::string getCurrentTime();
	std::string getCurrentThreadID();
	std::string formatFileName(const std::string& file);
	std::string prepareLogMessage(KOD::Logger::LogSeverity lvl, const std::string& message, const std::string& file,
	                              int line);

	KOD::Logger::LogSeverity m_minLogLevel = KOD::Logger::LogSeverity::FATAL;
	std::string m_filename;
	std::ofstream m_file;
	std::thread m_thread;
	std::condition_variable_any m_cv;
	std::queue<std::string> m_queue;
	std::atomic<KOD::Logger::ThreadState> m_state = KOD::Logger::ThreadState::RUNNING;
	size_t m_fileNameMaxCharacter = 25;
};
} // namespace KOD