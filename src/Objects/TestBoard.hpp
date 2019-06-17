#ifndef TESTBOARD_HPP
#define TESTBOARD_HPP

#include "Owner.hpp"

class TestBoard {
private:
    static void TestTakeOverFrom(Owner);
    static void TestBattle(Owner);
    static void TestTroopsArrived(Owner owner);

public:
    static void TestBoardInitialization();
    static void TestResolveBattlesCorrectness();
    static void TestResolveTroopsArrived();
    static void TestWinningCondition();
};

#endif // TESTBOARD_HPP
