#ifndef POSITION_HPP
#define POSITION_HPP

class Position {
private:
    unsigned int x;
    unsigned int y;

public:
    Position(unsigned int, unsigned int);

    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int distance(Position) const;
};

#endif // POSITION_HPP
