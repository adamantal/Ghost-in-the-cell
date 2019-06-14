#ifndef TESTUTILS_HPP
#define TESTUTILS_HPP

#include <string>

template<class T>
std::string stringify(T t){
    return t;
}

template<>
std::string stringify(unsigned int t) {
    return std::to_string(t);
}

template<class T>
void assertEquals(T expected, T actual) {
    if (expected != actual) {
        throw (stringify(expected) + std::string(" is expected, but got ") + stringify(actual));
    }
}

#endif // TESTUTILS_HPP
