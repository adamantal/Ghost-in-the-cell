#include "EntityStringBuilder.hpp"
#include "EntityStringBuilderException.hpp"

#include <sstream>

EntityStringBuilder::EntityStringBuilder(Id id,
                                         std::string entityType,
                                         short arg1) : id(id),
                                                       entityType(entityType),
                                                       arg1(arg1) {
}

bool EntityStringBuilder::validate() const {
    return (id != DEFAULT_ID) &&
           (!entityType.empty()) &&
           (!arg2.empty()) &&
           (!arg3.empty()) &&
           (!arg4.empty());
}

EntityStringBuilder& EntityStringBuilder::setArg2(unsigned int a2) {
    arg2 = a2;
    return *this;
}


EntityStringBuilder& EntityStringBuilder::setArg3(unsigned short a3) {
    arg3 = a3;
    return *this;
}

EntityStringBuilder& EntityStringBuilder::setArg3(Id a3) {
    arg3 = a3;
    return *this;
}

EntityStringBuilder& EntityStringBuilder::setArg4(unsigned short a4) {
    arg4 = a4;
    return *this;
}

EntityStringBuilder &EntityStringBuilder::setArg4(unsigned int a4) {
    arg4 = a4;
    return *this;
}

EntityStringBuilder& EntityStringBuilder::setArg4(short a4) {
    arg4 = a4;
    return *this;
}

EntityStringBuilder& EntityStringBuilder::setArg5(Distance a5) {
    arg5 = a5;
    return *this;
}

std::string EntityStringBuilder::build() const {
    if (!validate()) {
        throw EntityStringBuilderException("Missing fields detected during build.");
    }
    std::stringstream ss;
    ss << id << DELIMITER << entityType << DELIMITER << arg1 << DELIMITER << arg2 << DELIMITER << arg3 << DELIMITER
       << arg4 << DELIMITER;
    if (arg5.empty()) {
        ss << UNUSED_ARG;
    } else {
        ss << arg5;
    }
    return ss.str();
}
