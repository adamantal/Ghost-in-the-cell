#include "InjectableBoard.hpp"

void InjectableBoard::InjectFactory(FactoryPtr factory) {
    factories.push_back(factory);
}

void InjectableBoard::InjectTroop(TroopPtr troop) {
    troops.push_back(troop);
    // TODO optionally check whether origin/target is valid
}