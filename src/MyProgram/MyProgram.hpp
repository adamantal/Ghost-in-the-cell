#ifndef MYPROGRAM_HPP
#define MYPROGRAM_HPP

#include "Player.hpp"

namespace Heuristic {
    enum Player {
        Us = 1, Neutral = 0, Enemy = -1
    };
}

class MyProgram : public Player {
    virtual bool setup(std::string) override final;
};

#endif // MYPROGRAM_HPP
