#include "Position.hpp"

#include <algorithm>
#include <cmath>

Position::Position(unsigned int x, unsigned int y):x(x), y(y) {
}

unsigned int Position::getX() const {
    return x;
}

unsigned int Position::getY() const {
    return y;
}

unsigned int Position::distance(Position other) const {
    unsigned int deltaX = std::max(other.x, x) - std::min(other.x, x);
    unsigned int deltaY = std::max(other.y, y) - std::min(other.y, y);
    return (unsigned int) sqrt((deltaX * deltaX) + (deltaY * deltaY) - 1) + 1;
}



