#include "RandomPlayer.hpp"

#include <random>

int RandomPlayer::SelectFromSet(const std::set<int> &set) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, set.size() - 1);

    auto it(set.begin());
    advance(it, distr(gen));
    return *it;
}
