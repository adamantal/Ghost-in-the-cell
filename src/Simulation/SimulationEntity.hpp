#ifndef SIMULATIONENTITY_HPP
#define SIMULATIONENTITY_HPP

#include <memory>

#include "Player.hpp"

class SimulationEntity;
typedef std::shared_ptr<SimulationEntity> SimulationEntityPtr;

typedef unsigned int Points;

class SimulationEntity {
private:
    PlayerPtr player;
    Points points = 0;

public:
    SimulationEntity(PlayerPtr);
    PlayerPtr getPlayer() const;
    Points getPoints() const;
};

#endif // SIMULATIONENTITY_HPP
