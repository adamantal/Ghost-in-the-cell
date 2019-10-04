#include <cxxopts.hpp>

#include "logging.hpp"
#include "sample.hpp"

cxxopts::Options createOptions() {
    cxxopts::Options options("Ghost_in_the_cell", "Simulator and trainer for the Ghost in the cell game.");
    options.positional_help("[command]")
        .show_positional_help();
    options.add_options()
        ("command", "", cxxopts::value<std::string>())
        ("c,conf", "Configuration file", cxxopts::value<std::string>())
        ("d,debug", "Debug mode", cxxopts::value<bool>()->default_value("false"));
    options.parse_positional({"command"});
    return options;
}

int main(int argc, char* args[]) {
    cxxopts::Options options = createOptions();
    auto result = options.parse(argc, args);

    bool debugMode = result["debug"].as<bool>();
    setupLogger(debugMode);
    LOG_INFO("Logger initialized");

    if (!result.count("command")) {
        LOG_ERROR("No command defined");
        LOG_INFO(options.help());
        return 1;
    }

    std::string command = result["command"].as<std::string>();
    if (command == "sample") {
        runSample();
        return 0;
    } else if (command == "help") {
        LOG_INFO(options.help());
        return 0;
    } else {
        LOG_ERROR("The provided option is not legal");
        LOG_INFO(options.help());
        return 1;
    }
}
