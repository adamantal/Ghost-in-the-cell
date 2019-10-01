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
        TestBoard::TestWinningCondition();
        TestBoard::TestSendingBombAndTroops();
        TestBoard::TestPlayerOutputDigestedCorrectly();

        TestEntityStringBuilder::TestFactoryString();

        TestEntityWriter::TestFactoryWriter();
        TestEntityWriter::TestTroopWriter();
        TestEntityWriter::TestBombWriter();
    } catch (std::string& exc) {
        LOG_ERROR("Exception happened: {}", exc);
    } catch (std::exception& e) {
        LOG_ERROR("Exception happened: {}", e.what());
    } catch (const char* e) {
        LOG_ERROR("Exception happened: {}", e);
    }
}
