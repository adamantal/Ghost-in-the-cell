#ifndef POSITION_HPP
#define POSITION_HPP

class Position {
private:
    unsigned int x;
    unsigned int y;

public:
    Position(unsigned int, unsigned int);

    unsigned int GetX() const;
    unsigned int GetY() const;
    unsigned int Distance(Position) const;
};

#endif // POSITION_HPP
