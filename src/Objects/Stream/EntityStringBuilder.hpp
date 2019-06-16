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

    EntityStringBuilder& SetArg2(unsigned int);

    EntityStringBuilder& SetArg3(unsigned short);
    EntityStringBuilder& SetArg3(Id);
    EntityStringBuilder& SetArg3(short a3);

    EntityStringBuilder& SetArg4(unsigned short);
    EntityStringBuilder& SetArg4(unsigned int);
    EntityStringBuilder& SetArg4(short);

    EntityStringBuilder& SetArg5(Distance);

    std::string Build() const;
};


#endif // ENTITYSTRINGBUILDER_HPP
