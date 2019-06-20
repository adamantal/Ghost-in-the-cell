#include "logging.hpp"

#include "Program/Game.hpp"
#include "Program/Player.hpp"
#include "Program/DummyPlayer.hpp"
#include "Program/LazyPlayer.hpp"
#include "MyProgram/MyProgram.hpp"

int main() {
    setupLogger();

    spdlog::info("starting main");
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<LazyPlayer>();

    try {
        Game g(p1, p2);
        g.Run();
    } catch (const char* msg) {
        spdlog::error("Exception occured: {}", msg);
    } catch (std::string& msg) {
        spdlog::error("Exception occured: {}", msg);
    }

    return 0;
}
