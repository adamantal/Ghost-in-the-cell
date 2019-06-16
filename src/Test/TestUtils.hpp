#ifndef TESTUTILS_HPP
#define TESTUTILS_HPP

#include <string>
#include <src/Objects/Owner.hpp>

template<class T>
std::string Stringify(T t){
    return t;
}

template<>
std::string Stringify(unsigned int t);

template<>
std::string Stringify(Owner t);

template<class T>
void AssertEquals(T expected, T actual) {
    if (expected != actual) {
        throw (Stringify(expected) + std::string(" is expected, but got ") + Stringify(actual));
    }
}

void AssertTrue(bool expression);

#endif // TESTUTILS_HPP
