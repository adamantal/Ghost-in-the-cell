#include <iostream>

#include "Program/Game.hpp"
#include "Program/Player.hpp"
#include "Program/DummyPlayer.hpp"
#include "src/MyProgram/MyProgram.hpp"

int main() {
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<MyProgram>();

    Game g(p1, p2);
    g.run();

    return 0;
}
