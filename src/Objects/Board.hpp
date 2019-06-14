#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <list>
#include <string>
#include <memory>

#include "Factory.hpp"
#include "Troop.hpp"
#include "Link.hpp"
#include "Bomb.hpp"

static const unsigned short MIN_FACTORY_COUNT = 7;
static const unsigned short MAX_FACTORY_COUNT = 15;
static const unsigned int EXTRA_SPACE_BETWEEN_FACTORIES = 300;
static const unsigned int WIDTH = 16000;
static const unsigned int HEIGHT = 6500;
static const unsigned int MIN_PRODUCTION_RATE = 0;
static const unsigned int MAX_PRODUCTION_RATE = 3;
static const unsigned int PLAYER_INIT_UNITS_MIN = 15;
static const unsigned int PLAYER_INIT_UNITS_MAX = 30;

class Board;
typedef std::shared_ptr<Board> BoardPtr;

class Board {
private:
    std::list<FactoryPtr> factories;
    std::list<LinkPtr> links;

    std::list<TroopPtr> troops;
    std::list<BombPtr> bombs;

public:
    static BoardPtr createDefault();
    static BoardPtr createRandom();
    static BoardPtr createRandom(int seed);

    std::string getInitializationInput() const;
    std::string getInputForOwner(Owner owner) const;
    void digestOwnerOutput(std::string, Owner);

    void moveEntities();
    void produceNewCyborgs();
    void solveBattles();
    void explodeBombs();
    bool checkWinningCondition() const;
};

#endif // BOARD_HPP_INCLUDED
