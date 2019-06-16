#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <list>
#include <memory>
#include <string>
#include <vector>

#include "Factory.hpp"
#include "Troop.hpp"
#include "Link.hpp"
#include "Bomb.hpp"

const unsigned short MIN_FACTORY_COUNT = 7;
const unsigned short MAX_FACTORY_COUNT = 15;
const unsigned int EXTRA_SPACE_BETWEEN_FACTORIES = 300;
const unsigned int WIDTH = 16000;
const unsigned int HEIGHT = 6500;
const unsigned int MIN_PRODUCTION_RATE = 0;
const unsigned int MAX_PRODUCTION_RATE = 3;
const unsigned int MIN_TOTAL_PRODUCTION_RATE = 4;
const unsigned int PLAYER_INIT_UNITS_MIN = 15;
const unsigned int PLAYER_INIT_UNITS_MAX = 30;

class Board;
typedef std::shared_ptr<Board> BoardPtr;

class Board {
protected:
    std::vector<FactoryPtr> factories;
    std::list<LinkConstPtr> links;

    std::list<TroopPtr> troops;
    std::list<BombPtr> bombs;

public:
    static BoardPtr CreateDefault();
    static BoardPtr CreateRandom();
    static BoardPtr CreateRandom(int seed);

    std::string GetInitializationInput() const;
    std::string GetInputForOwner(Owner owner) const;
    void DigestOwnerOutput(std::string, Owner);

    void MoveEntities();
    void ProduceNewCyborgs();
    void SolveBattles();
    void ExplodeBombs();
    bool CheckWinningCondition() const;
};

#endif // BOARD_HPP_INCLUDED
