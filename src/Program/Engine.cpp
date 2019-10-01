#include "Engine.hpp"

#include <string>

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
    LOGGER_INFO(LOG, "{}. turn", turns++);
    LOGGER_INFO(playerLOG, "{}. turn", turns);

    BoardMetrics metrics = board->GetBoardMetrics();
    LOGGER_INFO(LOG, "metrics: " + metrics.toString());
    LOGGER_INFO(playerLOG, "metrics: " + metrics.toString());
    if (turns >= MAX_TURNS)
        return true;

    LOGGER_DEBUG(LOG, "collecting Player1's output");
    std::string player1Input = board->GetInputForOwner(Player1);
    LOGGER_INFO(playerLOG, "Player1's input");
    LOGGER_INFO(playerLOG, player1Input);

    std::string player1Output = player1->GetResponse(player1Input);
    LOGGER_INFO(playerLOG, "Player1's output");
    LOGGER_INFO(playerLOG, player1Output);

    LOGGER_DEBUG(LOG, "collecting Player2's output");
    std::string player2Input = board->GetInputForOwner(Player2);
    LOGGER_INFO(playerLOG, "Player2's input");
    LOGGER_INFO(playerLOG, player2Input);

    std::string player2Output = player2->GetResponse(player2Input);
    LOGGER_INFO(playerLOG, "Player2's output");
    LOGGER_INFO(playerLOG, player2Output);

    LOGGER_DEBUG(LOG, "execute player's orders");
    board->DigestOwnerOutput(player1Output, Player1);
    board->DigestOwnerOutput(player2Output, Player2);

    // move existing troops and bombs
    LOGGER_DEBUG(LOG, "Moving troops and bombs");
    board->MoveEntities();

    // produce new cyborgs in all factories
    LOGGER_DEBUG(LOG, "Producing new cyborgs");
    board->ProduceNewCyborgs();

    // solve battles
    LOGGER_DEBUG(LOG, "Resolving all battles");
    board->SolveBattles();

    // make bombs explode
    LOGGER_DEBUG(LOG, "Exploding bombs");
    board->ExplodeBombs();

    // check end conditions
    LOGGER_DEBUG(LOG, "Checking winning condition");
    return board->CheckWinningCondition();
}
