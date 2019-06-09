#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Player.hpp"

class Game {
private:
    PlayerPtr player1;
    PlayerPtr player2;

public:
    Game(PlayerPtr, PlayerPtr);

    PlayerPtr getPlayer1() const;
    PlayerPtr getPlayer2() const;

    void run();

    void getResults() const;
};

#endif // GAME_HPP_INCLUDED
