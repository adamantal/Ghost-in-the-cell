#include "Factory.hpp"

Factory::Factory(
        Id id,
        Owner owner,
        unsigned int cyborgs,
        unsigned short production,
        unsigned short badTurns):
    Entity(id, owner),
    cyborgs(cyborgs),
    production(production),
    badTurns(badTurns){
}

unsigned int Factory::getCyborgs() const {
    return cyborgs;
}

unsigned short Factory::getProduction() const {
    return production;
}

unsigned short Factory::getBadTurns() const {
    return badTurns;
}

void Factory::produceNewCyborgs() {
    if (getOwner() != Neutral) {
        cyborgs += production;
    }
}

void Factory::troopsArrived(unsigned int troops) {
    cyborgs += troops;
}

void Factory::decreaseCyborgs(unsigned int troops) {
    if (cyborgs >= troops) {
        cyborgs -= troops;
    } else {
        throw "Can't decrease cyborgs in factory with more than it has!";
    }
}

void Factory::takeOver(unsigned int troops, Owner newOwner) {
    if (cyborgs != 0) {
        throw "Can't take over factory, if there are still enemy troops present.";
    }
    setOwner(newOwner);
    cyborgs = troops;
}

void Factory::bombExploded() {
    decreaseCyborgs((cyborgs < 10) ? cyborgs : std::max((cyborgs + 1) / 2, (unsigned int) 10));
}
