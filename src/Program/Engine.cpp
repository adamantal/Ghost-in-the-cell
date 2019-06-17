#include "Engine.hpp"

#include <list>
#include <string>
#include <iostream>

Engine::Engine(PlayerPtr player1, PlayerPtr player2) :
        player1(player1),
        player2(player2) {
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
    std::cout << "Turn counter: " << turns++ << std::endl;
    if (turns >= MAX_TURNS)
        return true;

    // collect the player's moves
    std::cout << "Collecting Player1's output" << std::endl;
    std::string player1Input = board->GetInputForOwner(Player1);
    std::cout << player1Input << std::endl;
    std::string player1Output = player1->GetResponse(player1Input);
    std::cout << player1Output << std::endl;

    std::cout << "Collecting Player2's output" << std::endl;
    std::string player2Input = board->GetInputForOwner(Player2);
    std::cout << player2Input << std::endl;
    std::string player2Output = player2->GetResponse(player2Input);
    std::cout << player2Output << std::endl;

    // execute player's moves
    std::cout << "Execute player's orders" << std::endl;
    board->DigestOwnerOutput(player1Output, Player1);
    board->DigestOwnerOutput(player2Output, Player2);

    // move existing troops and bombs
    std::cout << "Moving troops and bombs" << std::endl;
    board->MoveEntities();

    // produce new cyborgs in all factories
    std::cout << "Producing new cyborgs" << std::endl;
    board->ProduceNewCyborgs();

    // solve battles
    std::cout << "Resolving all battles" << std::endl;
    board->SolveBattles();

    // make bombs explode
    std::cout << "Exploding bombs" << std::endl;
    board->ExplodeBombs();

    // check end conditions
    std::cout << "Checking winning condition" << std::endl;
    return board->CheckWinningCondition();
}
