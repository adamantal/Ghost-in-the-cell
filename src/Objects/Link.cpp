#include "Link.hpp"

Link::Link(unsigned int distance, FactoryPtr f1, FactoryPtr f2):
    distance(distance),
    f1(f1),
    f2(f2){
}

bool Link::Either(FactoryPtr f) const {
    return f == f1 || f == f2;
}

unsigned int Link::GetDistance() const {
    return distance;
}

FactoryPtr Link::Other(FactoryPtr f) const {
    if (f == f1) {
        return f2;
    } else if (f == f2) {
        return f1;
    } else {
        return nullptr;
    }
}

FactoryPtr Link::GetOne() const {
    return f1;
}

FactoryPtr Link::GetTwo() const {
    return f2;
}
