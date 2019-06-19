#include <iostream>

#include "spdlog/spdlog.h"

#include "Program/Game.hpp"
#include "Program/Player.hpp"
#include "Program/DummyPlayer.hpp"
#include "Program/LazyPlayer.hpp"
#include "MyProgram/MyProgram.hpp"

int main() {
    spdlog::info("Welcome to spdlog!");
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<LazyPlayer>();

    try {
        Game g(p1, p2);
        g.Run();
    } catch (const char* msg) {
        std::cout << "Exception occured: " << msg << std::endl;
    } catch (std::string& msg) {
        std::cout << "Exception occured: " << msg << std::endl;
    }

    return 0;
}
