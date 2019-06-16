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

FactoryPtr MovingEntity::GetTarget() const {
    return target;
}

FactoryPtr MovingEntity::GetOrigin() const {
    return origin;
}

Distance MovingEntity::GetTurns() const {
    return turns;
}

void MovingEntity::Move() {
    if (turns-- == 0) {
        throw MoveException("Can't move, already at target!");
    }
}
