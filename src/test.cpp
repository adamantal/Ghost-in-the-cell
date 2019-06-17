#include <iostream>

#include "src/Objects/Helper/TestPosition.hpp"
#include <src/Objects/TestBoard.hpp>
#include <src/Objects/Stream/TestEntityStringBuilder.hpp>
#include <src/Objects/Stream/TestEntityWriter.hpp>

int main() {
    try {
        TestPosition::TestDistance();

        TestBoard::TestBoardInitialization();
        TestBoard::TestResolveBattlesCorrectness();
        TestBoard::TestResolveTroopsArrived();
        TestBoard::TestPlayerOutputDigestedCorrectly();

        TestEntityStringBuilder::TestFactoryString();

        TestEntityWriter::TestFactoryWriter();
        TestEntityWriter::TestTroopWriter();
        TestEntityWriter::TestBombWriter();
    } catch (std::string& exc) {
        std::cout << "Exception happened: " << exc << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    } catch (const char* e) {
        std::cout << e << std::endl;
    }
}
