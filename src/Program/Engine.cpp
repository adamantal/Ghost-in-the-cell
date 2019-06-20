#include "Engine.hpp"

#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

Engine::Engine(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2) {
    LOG = spdlog::get("Main")->clone("Engine");
    playerLOG = spdlog::basic_logger_mt("Engine_file", "logs/runs/run.txt");
}

BoardPtr Engine::GetBoard() const {
    return board;
}

void Engine::SetTable(BoardPtr b) {
    board = b;
}

bool Engine::TakeTurn() {
    if (board == nullptr) {
        throw "Board is not initialized.";
    }
    SPDLOG_LOGGER_INFO(LOG, "{}. turn", turns++);
    SPDLOG_LOGGER_INFO(playerLOG, "{}. turn", turns);

    BoardMetrics metrics = board->GetBoardMetrics();
    SPDLOG_LOGGER_INFO(LOG, "Metrics: " + metrics.toString());
    SPDLOG_LOGGER_INFO(playerLOG, "Metrics: " + metrics.toString());
    if (turns >= MAX_TURNS)
        return true;

    SPDLOG_LOGGER_DEBUG(LOG, "collecting Player1's output");
    std::string player1Input = board->GetInputForOwner(Player1);
    SPDLOG_LOGGER_INFO(playerLOG, "Player1's input");
    SPDLOG_LOGGER_INFO(playerLOG, player1Input);

    std::string player1Output = player1->GetResponse(player1Input);
    SPDLOG_LOGGER_INFO(playerLOG, "Player1's output");
    SPDLOG_LOGGER_INFO(playerLOG, player1Output);

    SPDLOG_LOGGER_DEBUG(LOG, "collecting Player2's output");
    std::string player2Input = board->GetInputForOwner(Player2);
    SPDLOG_LOGGER_INFO(playerLOG, "Player2's input");
    SPDLOG_LOGGER_INFO(playerLOG, player2Input);

    std::string player2Output = player2->GetResponse(player2Input);
    SPDLOG_LOGGER_INFO(playerLOG, "Player2's output");
    SPDLOG_LOGGER_INFO(playerLOG, player2Output);

    SPDLOG_LOGGER_DEBUG(LOG, "execute player's orders");
    board->DigestOwnerOutput(player1Output, Player1);
    board->DigestOwnerOutput(player2Output, Player2);

    // move existing troops and bombs
    SPDLOG_LOGGER_DEBUG(LOG, "Moving troops and bombs");
    board->MoveEntities();

    // produce new cyborgs in all factories
    SPDLOG_LOGGER_DEBUG(LOG, "Producing new cyborgs");
    board->ProduceNewCyborgs();

    // solve battles
    SPDLOG_LOGGER_DEBUG(LOG, "Resolving all battles");
    board->SolveBattles();

    // make bombs explode
    SPDLOG_LOGGER_DEBUG(LOG, "Exploding bombs");
    board->ExplodeBombs();

    // check end conditions
    SPDLOG_LOGGER_DEBUG(LOG, "Checking winning condition");
    return board->CheckWinningCondition();
}
