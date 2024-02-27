#include "../LoggerDll/Logger.h"

#include <chrono>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <thread>

void threadDebug(KOD::Logger &logger)
{
	for (size_t i = 0; i < 1000; i++) {
		std::string log = std::string("text debug: ") + std::to_string(i);
		logger.log(KOD::Logger::LogSeverity::DEBUG, log.c_str());
	}
}

void threadInfo(KOD::Logger &logger)
{
	for (size_t i = 0; i < 1000; i++) {
		std::string log = std::string("text info: ") + std::to_string(i);
		logger.log(KOD::Logger::LogSeverity::INFO, log.c_str());
	}
}

void threadError(KOD::Logger &logger)
{
	for (size_t i = 0; i < 1000; i++) {
		std::string log = std::string("text error: ") + std::to_string(i);
		logger.log(KOD::Logger::LogSeverity::ERROR, log.c_str());
	}
}

int main()
{

	//std::thread td(threadDebug, std::ref(logger));
	//std::thread ti(threadInfo, std::ref(logger));
	//std::thread te(threadError, std::ref(logger));
	KOD::Logger logger;
	logger.setLogLevel(KOD::Logger::LogSeverity::DEBUG);
	logger.log(KOD::Logger::LogSeverity::INTERNAL, "internal");
	logger.log(KOD::Logger::LogSeverity::DEBUG, "debug 1 msg");
	logger.log(KOD::Logger::LogSeverity::INFO, "info 1 msg");
	logger.log(KOD::Logger::LogSeverity::WARNING, "warining 1 msg");
	logger.setFileNameMaxLenght(20);
	std::cout << "new setup for file name" << std::endl;
	logger.log(KOD::Logger::LogSeverity::ERROR, "error 1 msg");
	logger.log(KOD::Logger::LogSeverity::FATAL, "fatal 1 msg");

	logger.setLogLevel(KOD::Logger::LogSeverity::ERROR);
	logger.log(KOD::Logger::LogSeverity::DEBUG, "debug 2 msg");
	logger.log(KOD::Logger::LogSeverity::INFO, "info 2 msg");
	logger.log(KOD::Logger::LogSeverity::WARNING, "warining 2 msg");
	logger.log(KOD::Logger::LogSeverity::ERROR, "error 2 msg");
	logger.log(KOD::Logger::LogSeverity::FATAL, "fatal 2 msg");
	logger.stop();

	//td.join();
	//ti.join();
	//te.join();

	return 0;
}
