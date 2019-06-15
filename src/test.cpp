#include <iostream>

#include "src/Objects/Helper/TestPosition.hpp"
#include <src/Objects/TestBoard.hpp>
#include <src/Objects/Stream/TestEntityStringBuilder.hpp>
#include <src/Objects/Stream/TestEntityWriter.hpp>

int main() {
    try {
        TestPosition::testDistance();

        TestBoard::testBoardInitialization();
        TestBoard::testResolveBattlesCorrectness();

        TestEntityStringBuilder::testFactoryString();

        TestEntityWriter::testFactoryWriter();
        TestEntityWriter::testTroopWriter();
        TestEntityWriter::testBombWriter();
    } catch (std::string& exc) {
        std::cout << "Exception happened: " << exc << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}