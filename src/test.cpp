#include <iostream>

#include "src/Objects/Helper/TestPosition.hpp"

int main() {
    try {
        TestPosition::testDistance();
    } catch (std::string& exc) {
        std::cout << "Exception happened: " << exc << std::endl;
    }
}