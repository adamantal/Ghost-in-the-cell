#include "Engine.hpp"

#include <string>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

Engine::Engine(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2) {
    LOG = spdlog::get("main")->clone("Engine");
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
    LOG->info("{}. turn", turns++);
    playerLOG->info("{}. turn", turns);

    BoardMetrics metrics = board->GetBoardMetrics();
    LOG->info("Metrics: " + metrics.toString());
    playerLOG->info("Metrics: " + metrics.toString());
    if (turns >= MAX_TURNS)
        return true;

    // collect the player's moves
    LOG->debug("collecting Player1's output");
    std::string player1Input = board->GetInputForOwner(Player1);
    playerLOG->info("Player1's input");
    playerLOG->info(player1Input);

    std::string player1Output = player1->GetResponse(player1Input);
    playerLOG->info("Player1's output");
    playerLOG->info(player1Output);

    LOG->debug("Collecting Player2's output");
    std::string player2Input = board->GetInputForOwner(Player2);
    playerLOG->info("Player2's input");
    playerLOG->info(player2Input);

    std::string player2Output = player2->GetResponse(player2Input);
    playerLOG->info("Player2's output");
    playerLOG->info(player2Output);

    // execute player's moves
    LOG->debug("execute player's orders");
    board->DigestOwnerOutput(player1Output, Player1);
    board->DigestOwnerOutput(player2Output, Player2);

    // move existing troops and bombs
    LOG->debug("Moving troops and bombs");
    board->MoveEntities();

    // produce new cyborgs in all factories
    LOG->debug("Producing new cyborgs");
    board->ProduceNewCyborgs();

    // solve battles
    LOG->debug("Resolving all battles");
    board->SolveBattles();

    // make bombs explode
    LOG->debug("Exploding bombs");
    board->ExplodeBombs();

    // check end conditions
    LOG->debug("Checking winning condition");
    return board->CheckWinningCondition();
}
