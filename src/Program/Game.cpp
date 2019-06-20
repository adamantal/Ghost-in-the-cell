#include "Game.hpp"

#include "spdlog/spdlog.h"

Game::Game(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2),
        engine(player1, player2) {
    SPDLOG_INFO("initializing game");
    BoardPtr board = Board::CreateDefault();
    engine.SetTable(board);
    player1->Setup(board->GetInitializationInput());
    player2->Setup(board->GetInitializationInput());
    SPDLOG_INFO("game initialization ended");
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
    SPDLOG_INFO("game started");
    while (!engine.TakeTurn());
    SPDLOG_INFO("game successfully ended");
}
