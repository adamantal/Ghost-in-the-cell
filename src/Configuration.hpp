#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <map>
#include <string>

class Configuration {
private:
    static const std::string DELIMITER;

private:
    std::map<std::string, std::string> configs;
    static std::string searchDefault();

public:
    Configuration();
    void loadFromFile(std::string);
};

#endif // CONFIGURATION_HPP
