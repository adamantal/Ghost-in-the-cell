#include "TestBoard.hpp"

#include <string>

#include "Board.hpp"
#include "src/Test/TestUtils.hpp"
#include "src/Objects/Helper/InjectableBoard.hpp"

void TestBoard::testBoardInitialization() {
    std::string expected = std::string("11\n55\n0 1 2\n0 2 2\n0 3 5\n0 4 5\n0 5 5\n0 6 5\n0 7 2\n0 8 2\n0 9 8\n0 10 8\n") +
                           "1 2 5\n1 3 2\n1 4 7\n1 5 2\n1 6 7\n1 7 4\n1 8 3\n1 9 5\n1 10 11\n2 3 7\n2 4 2\n" +
                           "2 5 7\n2 6 2\n2 7 3\n2 8 4\n2 9 11\n2 10 5\n3 4 10\n3 5 3\n3 6 9\n3 7 6\n3 8 4\n" +
                           "3 9 4\n3 10 13\n4 5 9\n4 6 3\n4 7 4\n4 8 6\n4 9 13\n4 10 4\n5 6 10\n5 7 4\n5 8 6\n" +
                           "5 9 4\n5 10 13\n6 7 6\n6 8 4\n6 9 13\n6 10 4\n7 8 5\n7 9 9\n7 10 8\n8 9 8\n8 10 9\n9 10 17\n";

    BoardPtr board = Board::createDefault();
    assertEquals(expected, board->getInitializationInput());
}

void TestBoard::testResolveBattlesCorrectness() {
    InjectableBoardPtr board = std::make_shared<InjectableBoard>();

    Position pos(0, 0);
    FactoryPtr factory = std::make_shared<Factory>(100, Owner::Player1, pos, 5, 2);
    board->injectFactory(factory);

    TroopPtr troop1 = std::make_shared<Troop>(101, Owner::Player2, nullptr, factory, 0, 14);
    TroopPtr troop2 = std::make_shared<Troop>(102, Owner::Player1, nullptr, factory, 0, 8);
    board->injectTroop(troop1);
    board->injectTroop(troop2);

    board->solveBattles();
    assertEquals(Owner::Player2, factory->getOwner());
    assertEquals<unsigned int>(4, factory->getCyborgs());
}
