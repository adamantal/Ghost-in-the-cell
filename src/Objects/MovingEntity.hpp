#ifndef MOVINGENTITY_HPP_INCLUDED
#define MOVINGENTITY_HPP_INCLUDED

#include "Entity.hpp"
#include "Factory.hpp"
#include "Distance.hpp"

class MovingEntity : public Entity {
private:
    FactoryPtr origin;
    FactoryPtr target;
    Distance turns;

public:
    MovingEntity(Id, Owner, FactoryPtr, FactoryPtr, Distance);

    FactoryPtr GetTarget() const;
    FactoryPtr GetOrigin() const;
    Distance GetTurns() const;

    void Move();

};

#endif // MOVINGENTITY_HPP_INCLUDED
