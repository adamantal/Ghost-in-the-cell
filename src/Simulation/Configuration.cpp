#include "Configuration.hpp"

#include <fstream>

#include "Logging.hpp"
#include "StringUtils.hpp"

const std::string Configuration::DELIMITER = ":";

Configuration::Configuration() {
    std::string file = searchDefault();
    loadFromFile(file);
}

std::string Configuration::searchDefault() {
    return "../config";
}

void Configuration::loadFromFile(std::string file) {
    std::ifstream input(file);
    if (input.is_open()) {
        std::string line;
        unsigned int lineNumber = 0;
        while (getline(input, line)) {
            lineNumber++;
            StringUtils::trim(line);
            if (line.empty())
                continue;
            std::vector<std::string> conf = StringUtils::split(line, DELIMITER);
            if (conf.size() != 2) {
                LOG_WARN("Error while parsing configuration in line #{}", lineNumber);
                LOG_WARN("Content of the line: {}", line);
                continue;
            } else {
                configs[StringUtils::trim_copy(conf[0])] = StringUtils::trim_copy(conf[1]);
            }
        }
        LOG_DEBUG("Configuration parsed successfully from {}", file);
    } else {
        LOG_ERROR("Could not open configuration file {}", file);
        // TODO should throw exception here?
    }
}
