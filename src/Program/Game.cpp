#include "Game.hpp"

#include <iostream>

Game::Game(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2),
        engine(player1, player2) {
    std::cout << "Game is being created." << std::endl;
    BoardPtr board = Board::createDefault();
    engine.setTable(board);
    player1->setup(board->getInitializationInput());
    player2->setup(board->getInitializationInput());
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
    unsigned int i = 0;
    while (!engine.takeTurn()) {
        std::cout << i << std::endl;
    }
}
