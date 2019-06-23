#ifndef DUMMYPLAYER_HPP_INCLUDED
#define DUMMYPLAYER_HPP_INCLUDED

#include "Player.hpp"

class DummyPlayer : public Player {
    virtual bool Setup(std::string) {
        return true;
    }
    virtual std::string GetResponse(std::string) {
        return "WAIT\n";
    }
};

#endif // DUMMYPLAYER_HPP_INCLUDED
