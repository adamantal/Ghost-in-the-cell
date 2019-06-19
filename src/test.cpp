#include <iostream>

#include "Objects/Helper/TestPosition.hpp"
#include "Objects/TestBoard.hpp"
#include "Objects/Stream/TestEntityStringBuilder.hpp"
#include "Objects/Stream/TestEntityWriter.hpp"

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
