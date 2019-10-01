#ifndef LOGGING_HPP
#define LOGGING_HPP

// set up default log level to debug
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

// include spdlog library headers
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// let's wrap the spdlog implementation
#define LOG_ERROR SPDLOG_ERROR
#define LOG_INFO SPDLOG_INFO
#define LOG_DEBUG SPDLOG_DEBUG
#define LOG_TRACE SPDLOG_TRACE

#define LOGGER_INFO SPDLOG_LOGGER_INFO
#define LOGGER_DEBUG SPDLOG_LOGGER_DEBUG

// basic utility for setting up the logger
void setupLogger();

#endif // LOGGING_HPP
