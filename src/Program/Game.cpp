#include "Game.hpp"

Game::Game(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2),
        engine(player1, player2) {
}

PlayerPtr Game::getPlayer1() const {
    return player1;
}

PlayerPtr Game::getPlayer2() const {
    return player2;
}

std::string Game::getResults() const {
    return results;
}

void Game::run() {
    while (!engine.takeTurn());

}


