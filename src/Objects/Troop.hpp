#ifndef TROOP_HPP_INCLUDED
#define TROOP_HPP_INCLUDED

#include <memory>

#include "MovingEntity.hpp"
#include "Distance.hpp"

class Troop;
typedef std::shared_ptr<Troop> TroopPtr;
typedef std::shared_ptr<const Troop> TroopConstPtr;

class Troop : public MovingEntity {
private:
	unsigned int cyborgs;

public:
	Troop(Id, Owner, FactoryPtr, FactoryPtr, Distance, unsigned int);

    unsigned int GetCyborgs() const;
};

#endif // TROOP_HPP_INCLUDED
