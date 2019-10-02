#include "Position.hpp"

#include <algorithm>
#include <cmath>

Position::Position(unsigned int x, unsigned int y):x(x), y(y) {
}

unsigned int Position::GetX() const {
    return x;
}

unsigned int Position::GetY() const {
    return y;
}

unsigned int Position::Distance(Position other) const {
    unsigned int deltaX = std::max(other.x, x) - std::min(other.x, x);
    unsigned int deltaY = std::max(other.y, y) - std::min(other.y, y);
    if (deltaX == 0 && deltaY == 0) {
        throw "Positions are the same - this is probably not intended, error in logic";
    }
    return (unsigned int) sqrt((deltaX * deltaX) + (deltaY * deltaY) - 1) + 1;
}



