#include "Game.hpp"

#include <iostream>

Game::Game(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2),
        engine(player1, player2) {
    std::cout << "Initializing game..." << std::endl;
    BoardPtr board = Board::CreateDefault();
    engine.SetTable(board);
    player1->Setup(board->GetInitializationInput());
    player2->Setup(board->GetInitializationInput());
    std::cout << "Game initialization ended" << std::endl;
}

PlayerPtr Game::GetPlayer1() const {
    return player1;
}

PlayerPtr Game::GetPlayer2() const {
    return player2;
}

std::string Game::GetResults() const {
    return results;
}

void Game::Run() {
    std::cout << "Game started" << std::endl;
    unsigned int i = 0;
    while (!engine.TakeTurn()) {
        std::cout << i << std::endl;
    }
    std::cout << "Game successfully ended" << std::endl;
}
