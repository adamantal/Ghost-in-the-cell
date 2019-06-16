#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Board.hpp"
#include "Player.hpp"

class Engine {
private:
    const unsigned int MAX_TURNS = 200;

    BoardPtr board;
    PlayerPtr player1;
    PlayerPtr player2;

    unsigned int turns = 0;

public:
    Engine(PlayerPtr, PlayerPtr);

    void SetTable(BoardPtr);
    BoardPtr GetBoard() const;
    bool TakeTurn();
};

#endif // ENGINE_HPP
