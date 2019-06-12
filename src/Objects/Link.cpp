#include "Link.hpp"

Link::Link(unsigned int distance, FactoryPtr f1, FactoryPtr f2):
    distance(distance),
    f1(f1),
    f2(f2){
}

bool Link::either(FactoryPtr f) const {
    return f == f1 || f == f2;
}

unsigned int Link::getDistance() const {
    return distance;
}

FactoryPtr Link::other(FactoryPtr f) const {
    if (f == f1) {
        return f2;
    } else if (f == f2) {
        return f1;
    } else {
        return nullptr;
    }
}

FactoryPtr Link::getOne() const {
    return f1;
}

FactoryPtr Link::getTwo() const {
    return f2;
}
