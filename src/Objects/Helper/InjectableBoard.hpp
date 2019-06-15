#ifndef INJECTABLEBOARD_HPP
#define INJECTABLEBOARD_HPP

#include <memory>

#include "Board.hpp"

class InjectableBoard;
typedef std::shared_ptr<InjectableBoard> InjectableBoardPtr;

class InjectableBoard : public Board {
public:
    void injectFactory(FactoryPtr factory);
    void injectLink(LinkConstPtr link);
    void injectTroop(TroopPtr troop);
    void injectBomb(BombPtr bomb);
};


#endif // INJECTABLEBOARD_HPP
