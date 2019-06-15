#ifndef TESTUTILS_HPP
#define TESTUTILS_HPP

#include <string>
#include <src/Objects/Owner.hpp>

template<class T>
std::string stringify(T t){
    return t;
}

template<>
std::string stringify(unsigned int t);

template<>
std::string stringify(Owner t);

template<class T>
void assertEquals(T expected, T actual) {
    if (expected != actual) {
        throw (stringify(expected) + std::string(" is expected, but got ") + stringify(actual));
    }
}

void assertTrue(bool expression);

#endif // TESTUTILS_HPP
