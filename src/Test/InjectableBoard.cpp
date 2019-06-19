#include "InjectableBoard.hpp"

void InjectableBoard::InjectFactory(FactoryPtr factory) {
    factories.push_back(factory);
}

void InjectableBoard::InjectTroop(TroopPtr troop) {
    troops.push_back(troop);
}

void InjectableBoard::InjectLink(LinkConstPtr link) {
    links.push_back(link);
}

std::list<TroopPtr> InjectableBoard::GetTroops() const {
    return troops;
}
