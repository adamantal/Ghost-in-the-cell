#ifndef SIMULATIONENTITY_HPP
#define SIMULATIONENTITY_HPP

class SimulationEntity;
typedef std::shared_ptr<SimulationEntity> SimulationEntityPtr;

class SimulationEntity {
private:
    PlayerPtr player;
    unsigned int points = 0;

public:
    SimulationEntity(PlayerPtr);
};

#endif // SIMULATIONENTITY_HPP
