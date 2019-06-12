#ifndef BOMB_HPP_INCLUDED
#define BOMB_HPP_INCLUDED

#include <memory>

#include "MovingEntity.hpp"

class Bomb;
typedef std::shared_ptr<Bomb> BombPtr;
typedef std::shared_ptr<const Bomb> BombConstPtr;

class Bomb : public MovingEntity {
public:
    Bomb(Id id, Owner owner, FactoryPtr origin, FactoryPtr target, Distance turns):
        MovingEntity(id, owner, origin, target, turns) {
    }
};

#endif // BOMB_HPP_INCLUDED
