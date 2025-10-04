#include "exceptionClass.h"

// Constructor stores the desired error message passed in.
MyException::MyException(const std::string& msg) : message(msg) {}

// Override the std::exception what()
// Returns the stored error message as a c string
const char* MyException::what() const noexcept
{
    return message.c_str();
}
