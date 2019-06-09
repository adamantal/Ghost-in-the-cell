#include <iostream>

#include "Program/Game.hpp"
#include "Program/Player.hpp"
#include "Program/DummyPlayer.hpp"

int main() {
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<DummyPlayer>();

    Game m(p1, p2);

    return 0;
}
