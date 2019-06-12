#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include <list>
#include <string>
#include <memory>

#include "Factory.hpp"
#include "Troop.hpp"
#include "Link.hpp"
#include "Bomb.hpp"

const short MIN_NUMBER_OF_FACTORIES = 7;
const short MAX_NUMBER_OF_FACTORIES = 15;
const short MIN_NUMBER_OF_LINKS = 21;
const short MAX_NUMBER_OF_LINKS = 105;
const short MAX_NUMBER_OF_DISTANCE = 20;

class Board;
typedef std::shared_ptr<Board> BoardPtr;

class Board {
private:
    const std::list<FactoryPtr> factories;
    const std::list<LinkPtr> links;

    std::list<TroopPtr> troops;
    std::list<BombPtr> bombs;

public:
    static Board createDefault();

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
