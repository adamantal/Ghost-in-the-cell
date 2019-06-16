#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <memory>
#include <string>

#include "Player.hpp"
#include "Engine.hpp"

class Game;
typedef std::shared_ptr<Game> GamePtr;

class Game {
private:
    PlayerPtr player1;
    PlayerPtr player2;
    Engine engine;

    std::string results;

public:
    Game(PlayerPtr, PlayerPtr);

    PlayerPtr GetPlayer1() const;
    PlayerPtr GetPlayer2() const;

    std::string GetResults() const;
    void Run();
};

#endif // GAME_HPP_INCLUDED
