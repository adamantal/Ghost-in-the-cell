#include "Troop.hpp"

Troop::Troop(
        Id id,
        Owner owner,
        FactoryPtr origin,
        FactoryPtr target,
        Distance turns,
        unsigned int cyborgs):
    MovingEntity(id, owner, origin, target, turns),
    cyborgs(cyborgs){
}

unsigned int Troop::GetCyborgs() const {
    return cyborgs;
}
