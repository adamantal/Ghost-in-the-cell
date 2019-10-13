#include "Logging.hpp"

#include <experimental/filesystem>

void setupLogger(bool debug) {
    spdlog::set_level(spdlog::level::debug);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    if (debug) {
        console_sink->set_level(spdlog::level::debug);
    } else {
        console_sink->set_level(spdlog::level::info);
    }

    std::experimental::filesystem::create_directory("./logs");
    std::experimental::filesystem::create_directory("./logs/runs");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/main.txt", true);
    file_sink->set_level(spdlog::level::debug);

    auto logger = std::make_shared<spdlog::logger>("Main", (spdlog::sinks_init_list) {console_sink, file_sink});
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);

    LOG_INFO("Logger initialized");
}
