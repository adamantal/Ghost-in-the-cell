#ifndef BOARDMETIRCS_HPP
#define BOARDMETIRCS_HPP

#include <string>

class BoardMetrics {
private:
    unsigned int player1Points;
    unsigned int player2Points;

    unsigned int player1Production;
    unsigned int player2Production;

public:
    BoardMetrics(unsigned int, unsigned int, unsigned int, unsigned int);

    std::string toString() const;
};

#endif // BOARDMETIRCS_HPP
