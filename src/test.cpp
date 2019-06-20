#include "logging.hpp"

#include "Objects/Helper/TestPosition.hpp"
#include "Objects/TestBoard.hpp"
#include "Objects/Stream/TestEntityStringBuilder.hpp"
#include "Objects/Stream/TestEntityWriter.hpp"

int main() {
    setupLogger();
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
        spdlog::error("Exception happened: {}", exc);
    } catch (std::exception& e) {
        spdlog::error("Exception happened: {}", e.what());
    } catch (const char* e) {
        spdlog::error("Exception happened: {}", e);
    }
}
