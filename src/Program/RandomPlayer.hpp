#ifndef RANDOMPLAYER_HPP
#define RANDOMPLAYER_HPP

#include <set>

#include "LazyPlayer.hpp"

class RandomPlayer : public LazyPlayer {
protected:
    virtual int SelectFromSet(const std::set<int>& set) override;
};


#endif // RANDOMPLAYER_HPP
