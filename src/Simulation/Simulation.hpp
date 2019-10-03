#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <memory>
#include <list>

#include "Player.hpp"

class Simulation;
typedef std::shared_ptr<Simulation> SimulationPtr;

class Simulation {
private:
    std::list<SimulationEntityPtr> currentPlayers;

public:
    Simulation();

    void AddPlayer(PlayerPtr);
    void RunEpoch();
};

#endif // SIMULATION_HPP
