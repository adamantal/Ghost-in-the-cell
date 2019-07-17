#include "Factory.hpp"

Factory::Factory(
        Id id,
        Owner owner,
        Position position,
        unsigned int cyborgs,
        unsigned short production):
    Entity(id, owner),
    position(position),
    cyborgs(cyborgs),
    production(production) {
}

unsigned int Factory::GetCyborgs() const {
    return cyborgs;
}

unsigned short Factory::GetProduction() const {
    return production;
}

unsigned short Factory::GetBadTurns() const {
    return badTurns;
}

Position Factory::GetPosition() const {
    return position;
}

void Factory::ProduceNewCyborgs() {
    if (GetOwner() != Neutral) {
        cyborgs += production;
    }
}

void Factory::TroopsArrived(unsigned int troops) {
    cyborgs += troops;
}

void Factory::DecreaseCyborgs(unsigned int troops) {
    if (cyborgs >= troops) {
        cyborgs -= troops;
    } else {
        throw "Can't decrease cyborgs in factory with more than it has!";
    }
}

void Factory::TakeOver(unsigned int troops, Owner newOwner) {
    if (cyborgs != 0) {
        throw "Can't take over factory, if there are still enemy troops present.";
    }
    SetOwner(newOwner);
    cyborgs = troops;
}

void Factory::BombExploded() {
    DecreaseCyborgs((cyborgs < 10) ? cyborgs : std::max((cyborgs + 1) / 2, (unsigned int) 10));
}

void Factory::IncreaseProductionDuringSetup() {
    production++;
}

void Factory::AttemptProductionIncrease() {
    // TODO test case where production is 3 and an increase is attempted
    // TODO test case where there are less than 10 cyborgs
    // TODO test case where both condition is satisfied
    if (production < 3 && cyborgs >= 10) {
        cyborgs -= 10;
        production += 1;
    }
}
