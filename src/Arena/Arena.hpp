#ifndef ARENA_HPP
#define ARENA_HPP

#include <memory>
#include <list>

#include "Player.hpp"

class Arena;
typedef std::shared_ptr<Arena> ArenaPtr;

class Arena {
private:
    std::list<PlayerPtr> currentPlayers;

public:
    Arena();
    void AddPlayer(PlayerPtr);

    void RunEpoch();
};

#endif // ARENA_HPP
