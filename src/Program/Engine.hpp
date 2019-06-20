#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "spdlog/spdlog.h"

#include "Objects/Board.hpp"
#include "Program/Player.hpp"

class Engine {
private:
    const unsigned int MAX_TURNS = 200;

    std::shared_ptr<spdlog::logger> LOG;
    std::shared_ptr<spdlog::logger> playerLOG;

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
