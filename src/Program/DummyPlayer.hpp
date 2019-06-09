#ifndef DUMMYPLAYER_HPP_INCLUDED
#define DUMMYPLAYER_HPP_INCLUDED

#include "Player.hpp"

class DummyPlayer : public Player {
    virtual bool setup(std::string setup) {
        return "";
    }
    virtual std::string getResponse(std::string input) {
        return "";
    }
};

#endif // DUMMYPLAYER_HPP_INCLUDED
