#ifndef FACTORY_HPP_INCLUDED
#define FACTORY_HPP_INCLUDED

#include <memory>

#include "Entity.hpp"

class Factory;
typedef std::shared_ptr<Factory> FactoryPtr;
typedef std::shared_ptr<const Factory> FactoryConstPtr;

class Factory : public Entity {
private:
    unsigned int cyborgs;
    unsigned short production;
    unsigned short badTurns;

public:
    Factory(Id, Owner, unsigned int, unsigned short, unsigned short);

    unsigned int getCyborgs() const;
    unsigned short getProduction() const;
    unsigned short getBadTurns() const;

    void produceNewCyborgs();

    void troopsArrived(unsigned int);
    void decreaseCyborgs(unsigned int);
    void takeOver(unsigned int, Owner);

    void bombExploded();
};

#endif // FACTORY_HPP_INCLUDED
