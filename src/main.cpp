#include "logging.hpp"
#include "sample.hpp"

void printUsage() {
    LOG_INFO("executable <option> <arguments>");
    LOG_INFO("\t\t<option> is one of the following:");
    LOG_INFO("\t\t\tsample - starts a game between Players");
    LOG_INFO("\t\t\thelp - print this message");
}

int main(int argc, char* args[]) {
    setupLogger();
    LOG_INFO("Logger initialized");

    if (argc == 1) {
        LOG_WARN("No option provided.");
        printUsage();
        return 0;
    }

    std::string command (args[1]);
    if (command == "sample") {
        runSample();
        return 0;
    } else if (command == "help") {
        printUsage();
        return 0;
    } else {
        LOG_ERROR("The provided option is not legal");
        printUsage();
        return 1;
    }
}
