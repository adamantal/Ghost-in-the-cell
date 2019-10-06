#include "TestUtils.hpp"

template<>
std::string Stringify(unsigned int t) {
    return std::to_string(t);
}

template<>
std::string Stringify(int t) {
    return std::to_string(t);
}

template<>
std::string Stringify(Owner t) {
    switch (t) {
        case Owner::Player1:
            return "Player1";
        case Owner::Player2:
            return "Player2";
        case Owner::Neutral:
            return "Neutral";
        default:
            throw "This Owner is not implemented for Stringify.";
    }
}

void AssertTrue(bool expression) {
    if (!expression) {
        throw "Expression is not true!";
    }
}

void AssertFalse(bool expression) {
    if (expression) {
        throw "Expression is not false!";
    }
}
