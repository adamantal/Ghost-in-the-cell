#include "TestPosition.hpp"

#include "Position.hpp"
#include "src/Test/TestUtils.hpp"

void TestPosition::testDistance() {
    {
        Position p1(0, 0);
        Position p2(3, 4);
        assertEquals<unsigned int>(5, p1.distance(p2));
    }
    {
        Position p1(0, 0);
        Position p2(3, 5);
        assertEquals<unsigned int>(6, p1.distance(p2));
    }
    {
        Position p1(0, 0);
        Position p2(3, 6);
        assertEquals<unsigned int>(7, p1.distance(p2));
    }
    {
        Position p1(0, 0);
        Position p2(3, 7);
        assertEquals<unsigned int>(8, p1.distance(p2));
    }
    {
        Position p1(0, 0);
        Position p2(4, 7);
        assertEquals<unsigned int>(9, p1.distance(p2));
    }
}
