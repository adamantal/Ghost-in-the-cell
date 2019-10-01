#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "logging.hpp"

#include "Board.hpp"
#include "Player.hpp"

class Engine {
private:
    const unsigned int MAX_TURNS = 200;

    std::shared_ptr<LOGGER> LOG;
    std::shared_ptr<LOGGER> playerLOG;

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
