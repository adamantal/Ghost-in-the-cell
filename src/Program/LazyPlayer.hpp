#ifndef LAZYPLAYER_HPP
#define LAZYPLAYER_HPP

#include <set>
#include "Player.hpp"

class LazyPlayer : public Player {
protected:
    virtual int SelectFromSet(const std::set<int>& set);

public:
    virtual bool Setup(std::string) override final;
    virtual std::string GetResponse(std::string) override final;
};

#endif // LAZYPLAYER_HPP
