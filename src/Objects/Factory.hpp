#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED

#include <memory>

#include "Entity.hpp"
#include "src/Objects/Helper/Position.hpp"

class Factory;
typedef std::shared_ptr<Factory> FactoryPtr;
typedef std::shared_ptr<const Factory> FactoryConstPtr;

class Factory : public Entity {
private:
    unsigned int cyborgs;
    unsigned short production;
    unsigned short badTurns = 0;

    Position position;

public:
    Factory(Id, Owner, Position, unsigned int, unsigned short);

    unsigned int GetCyborgs() const;
    unsigned short GetProduction() const;
    unsigned short GetBadTurns() const;
    Position GetPosition() const;

    void IncreaseProductionDuringSetup();

    void ProduceNewCyborgs();

    void TroopsArrived(unsigned int);
    void DecreaseCyborgs(unsigned int);
    void TakeOver(unsigned int, Owner);

    void BombExploded();
};

#endif // FACTORY_HPP_INCLUDED
