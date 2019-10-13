#include "Simulation.hpp"

void Simulation::AddPlayer(PlayerPtr player) {
    SimulationEntityPtr entity = std::make_shared<SimulationEntity>(player);
    currentPlayers.push_back(entity);
}

void Simulation::RunEpoch() {
    // run matches between each player-player pair
    // roll over to the new generation of players
}
