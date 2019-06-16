#include <iostream>

#include "Program/Game.hpp"
#include "Program/Player.hpp"
#include "Program/DummyPlayer.hpp"
#include "Program/RandomPlayer.hpp"
#include "src/MyProgram/MyProgram.hpp"

int main() {
    PlayerPtr p1 = std::make_shared<DummyPlayer>();
    PlayerPtr p2 = std::make_shared<RandomPlayer>();

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
