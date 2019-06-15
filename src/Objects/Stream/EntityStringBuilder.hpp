#ifndef ENTITYSTRINGBUILDER_HPP
#define ENTITYSTRINGBUILDER_HPP

#include <string>
#include <src/Objects/Distance.hpp>

#include "Id.hpp"

class EntityStringBuilder {
private:
    const std::string DELIMITER = " ";
    const std::string UNUSED_ARG = "0";

    Id id;
    std::string entityType;
    short arg1;
    std::string arg2;
    std::string arg3;
    std::string arg4;
    std::string arg5;

    bool validate() const;

public:
    EntityStringBuilder(Id, std::string, short);

    EntityStringBuilder& setArg2(unsigned int);

    EntityStringBuilder& setArg3(unsigned short);
    EntityStringBuilder& setArg3(Id);
    EntityStringBuilder& setArg3(short a3);

    EntityStringBuilder& setArg4(unsigned short);
    EntityStringBuilder& setArg4(unsigned int);
    EntityStringBuilder& setArg4(short);

    EntityStringBuilder& setArg5(Distance);

    std::string build() const;
};


#endif // ENTITYSTRINGBUILDER_HPP
