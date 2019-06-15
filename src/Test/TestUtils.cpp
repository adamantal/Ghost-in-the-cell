#include "TestUtils.hpp"

template<>
std::string stringify(unsigned int t) {
    return std::to_string(t);
}

template<>
std::string stringify(Owner t) {
    switch (t) {
        case Owner::Player1:
            return "Player1";
        case Owner::Player2:
            return "Player2";
        case Owner::Neutral:
            return "Neutral";
        default:
            throw "This Owner is not implemented for stringify.";
    }
}

void assertTrue(bool expression) {
    if (!expression) {
        throw "Expression is not true!";
    }
}