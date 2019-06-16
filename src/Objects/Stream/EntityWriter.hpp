#ifndef ENTITYWRITER_HPP
#define ENTITYWRITER_HPP

#include <string>
#include <src/Objects/Factory.hpp>
#include <src/Objects/Troop.hpp>
#include <src/Objects/Bomb.hpp>

namespace EntityTypes {
    const std::string BOMB = "BOMB";
    const std::string FACTORY = "FACTORY";
    const std::string TROOP = "TROOP";
}

class EntityWriter {
private:
    static short convertOwner(Owner, Owner);

public:
    static std::string Write(const FactoryConstPtr &, Owner);
    static std::string Write(const TroopConstPtr &, Owner);
    static std::string Write(const BombConstPtr &, Owner);
};

#endif // ENTITYWRITER_HPP
