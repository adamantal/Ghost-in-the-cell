#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include "Program/Game.hpp"
#include "Program/Player.hpp"
#include "Program/DummyPlayer.hpp"
#include "Program/LazyPlayer.hpp"
#include "MyProgram/MyProgram.hpp"

void setupLogger() {
    spdlog::set_level(spdlog::level::debug);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/main.txt", true);
    file_sink->set_level(spdlog::level::debug);

    auto logger = std::make_shared<spdlog::logger>("main", (spdlog::sinks_init_list) {console_sink, file_sink});
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
}

int main() {
    setupLogger();

    spdlog::info("starting main");
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<LazyPlayer>();

    try {
        Game g(p1, p2);
        g.Run();
    } catch (const char* msg) {
        spdlog::error("Exception occured: {}", msg);
    } catch (std::string& msg) {
        spdlog::error("Exception occured: {}", msg);
    }

    return 0;
}
