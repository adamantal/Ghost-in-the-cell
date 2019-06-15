#ifndef BOARDSERIALIZER_HPP
#define BOARDSERIALIZER_HPP

#include <sstream>

#include "Link.hpp"

class InitStringBuilder {
private:
    unsigned int factorySize;
    unsigned int linkSize;
    std::stringstream linkStream;

public:
    InitStringBuilder(unsigned int, unsigned int);

    void addLink(const LinkConstPtr& link);
    std::string build() const;
};

#endif // BOARDSERIALIZER_HPP
