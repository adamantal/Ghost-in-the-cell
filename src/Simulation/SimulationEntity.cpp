#include "SimulationEntity.hpp"

SimulationEntity::SimulationEntity(PlayerPtr player):
        player(player) {
}

PlayerPtr SimulationEntity::getPlayer() const {
    return player;
}

Points SimulationEntity::getPoints() const {
    return points;
}
