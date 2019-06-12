#ifndef MOVEEXCEPTION_HPP
#define MOVEEXCEPTION_HPP

#include <exception>
#include <string>

class MoveException : std::exception {
private:
    std::string message;

public:
    MoveException(std::string message) :
        message(message) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif // MOVEEXCEPTION_HPP
