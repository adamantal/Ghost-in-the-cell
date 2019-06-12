#ifndef ENTITYSTRINGBUILDEREXCEPTION_HPP
#define ENTITYSTRINGBUILDEREXCEPTION_HPP

#include <exception>
#include <string>

class EntityStringBuilderException : std::exception {
private:
    std::string message;

public:
    EntityStringBuilderException(std::string message) :
            message(message) {
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};

#endif // ENTITYSTRINGBUILDEREXCEPTION_HPP
