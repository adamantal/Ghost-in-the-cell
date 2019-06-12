#include "MovingEntity.hpp"
#include "MoveException.hpp"

MovingEntity::MovingEntity(
        Id id,
        Owner owner,
        FactoryPtr origin,
        FactoryPtr target,
        Distance turns):
    Entity(id, owner),
    origin(origin),
    target(target),
    turns(turns) {
}

FactoryPtr MovingEntity::getTarget() const {
    return target;
}

FactoryPtr MovingEntity::getOrigin() const {
    return origin;
}

Distance MovingEntity::getTurns() const {
    return turns;
}

void MovingEntity::move() {
    if (turns-- == 0) {
        throw MoveException("Can't move, already at target!");
    }
}
