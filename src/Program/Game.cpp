#include "Game.hpp"

Game::Game(PlayerPtr player1_, PlayerPtr player2_) {
    player1 = player1_;
    player2 = player2_;
}

PlayerPtr Game::getPlayer1() const {
    return player1;
}

PlayerPtr Game::getPlayer2() const {
    return player2;
}

void Game::run() {

}

void Game::getResults() const {
}
