#include "logging.hpp"

#include "Program/Game.hpp"
#include "Player/Player.hpp"
#include "Player/DummyPlayer.hpp"
#include "Player/LazyPlayer.hpp"
#include "Player/HumanPlayer.hpp"

int main() {
    setupLogger();

    SPDLOG_INFO("starting main");
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<LazyPlayer>();

    try {
        Game g(p1, p2);
        g.Run();
    } catch (const char* msg) {
        SPDLOG_ERROR("Exception occured: {}", msg);
    } catch (std::string& msg) {
        SPDLOG_ERROR("Exception occured: {}", msg);
    }

    return 0;
}
