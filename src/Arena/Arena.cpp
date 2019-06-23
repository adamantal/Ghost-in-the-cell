#include "Arena.hpp"

void Arena::AddPlayer(PlayerPtr player) {
    currentPlayers.push_back(player);
}

void Arena::RunEpoch() {
    // run matches between each player-player pair
    // roll over to the new generation of players
}
