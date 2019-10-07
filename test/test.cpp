#include <cxxopts.hpp>

#include "Logging.hpp"

#include "Objects/TestPosition.hpp"
#include "Objects/TestBoard.hpp"
#include "Objects/Stream/TestEntityStringBuilder.hpp"
#include "Objects/Stream/TestEntityWriter.hpp"
#include "TestStringUtils.hpp"

cxxopts::Options createOptions() {
    cxxopts::Options options("Test", "Runs all the tests");
    options.add_options()
        ("d,debug", "Debug mode", cxxopts::value<bool>()->default_value("false"));
    return options;
}

int main(int argc, char* args[]) {
    cxxopts::Options options = createOptions();
    auto result = options.parse(argc, args);
    setupLogger(result["debug"].as<bool>());

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

        TestStringUtils::TestSplit();
        TestStringUtils::TestTrim();
    } catch (std::string& exc) {
        LOG_ERROR("Exception happened: {}", exc);
    } catch (std::exception& e) {
        LOG_ERROR("Exception happened: {}", e.what());
    } catch (const char* e) {
        LOG_ERROR("Exception happened: {}", e);
    }
}
