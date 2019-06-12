#ifndef DUMMYPLAYER_HPP_INCLUDED
#define DUMMYPLAYER_HPP_INCLUDED

#include "Player.hpp"

class DummyPlayer : public Player {
    virtual bool setup(std::string setup) {
        return true;
    }
    virtual std::string getResponse(std::string input) {
        return "WAIT\n";
    }
};

#endif // DUMMYPLAYER_HPP_INCLUDED
