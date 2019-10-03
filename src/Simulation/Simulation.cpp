#include "Simulation.hpp"

void Simulation::AddPlayer(PlayerPtr player) {
    currentPlayers.push_back(player);
}

void Simulation::RunEpoch() {
    // run matches between each player-player pair
    // roll over to the new generation of players
}
