#include "logging.hpp"

void setupLogger() {
    spdlog::set_level(spdlog::level::debug);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/main.txt", true);
    file_sink->set_level(spdlog::level::debug);

    auto logger = std::make_shared<spdlog::logger>("Main", (spdlog::sinks_init_list) {console_sink, file_sink});
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
}
