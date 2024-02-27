# LoggerDll

It is a DLL library that provides a basic multi-threaded logger
## Installation

## Usage

```cpp
KOD::Logger logger;
logger.setLogLevel(KOD::Logger::LogSeverity::DEBUG);
logger.log(KOD::Logger::LogSeverity::DEBUG, "debug 1 msg");
logger.log(KOD::Logger::LogSeverity::INFO, "info 1 msg");
logger.log(KOD::Logger::LogSeverity::WARNING, "warining 1 msg");
logger.setFileNameMaxLenght(20);
logger.log(KOD::Logger::LogSeverity::ERROR, "error 1 msg");
logger.log(KOD::Logger::LogSeverity::FATAL, "fatal 1 msg");

logger.setLogLevel(KOD::Logger::LogSeverity::ERROR);
logger.log(KOD::Logger::LogSeverity::DEBUG, "debug 2 msg");
logger.log(KOD::Logger::LogSeverity::INFO, "info 2 msg");
logger.log(KOD::Logger::LogSeverity::WARNING, "warining 2 msg");
logger.log(KOD::Logger::LogSeverity::ERROR, "error 2 msg");
logger.log(KOD::Logger::LogSeverity::FATAL, "fatal 2 msg");
logger.stop();
```
## Output
```
2024:27 07:33:38.225 | 11184  |INTERNAL | LOGGER DLL               :0     | --== LOGGER INITIALIZED ==--
2024:27 07:33:38.228 | 11184  |DEBUG    | ...LoggerExample\main.cpp:42    | debug 1 msg
2024:27 07:33:38.228 | 11184  |INFO     | ...LoggerExample\main.cpp:43    | info 1 msg
2024:27 07:33:38.228 | 11184  |WARNING  | ...LoggerExample\main.cpp:44    | warining 1 msg
2024:27 07:33:38.228 | 11184  |ERROR    | ...rExample\main.cpp:47    | error 1 msg
2024:27 07:33:38.228 | 11184  |FATAL    | ...rExample\main.cpp:48    | fatal 1 msg
2024:27 07:33:38.228 | 11184  |ERROR    | ...rExample\main.cpp:54    | error 2 msg
2024:27 07:33:38.228 | 11184  |FATAL    | ...rExample\main.cpp:55    | fatal 2 msg
2024:27 07:33:38.228 | 11184  |INTERNAL | LOGGER DLL          :0     | --== LOGGER STOPPING ==--

```