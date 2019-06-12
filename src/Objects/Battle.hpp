#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <vector>

#include "Factory.hpp"
#include "Troop.hpp"

class Battle {
private:
    FactoryPtr factory;
    std::vector<Troop> troops;

public:
    Battle(Factory);
    void addTroop(Troop);
    Troop resolve();
};


#endif // BATTLE_HPP
