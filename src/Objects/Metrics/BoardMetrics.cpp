#include "BoardMetrics.hpp"

#include <sstream>

BoardMetrics::BoardMetrics(
        unsigned int p1points,
        unsigned int p2points,
        unsigned int p1Production,
        unsigned int p2Production):
    player1Points(p1points),
    player2Points(p2points),
    player1Production(p1Production),
    player2Production(p2Production) {
}

std::string BoardMetrics::toString() const {
    std::stringstream ss;
    ss << "points [" << player1Points << "//" << player2Points << "], " <<
        "production (" << player1Production << "//" << player2Production << ")";
    return ss.str();
}
