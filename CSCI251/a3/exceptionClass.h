#ifndef EXCEPTIONCLASS_H
#define EXCEPTIONCLASS_H

#include <exception>
#include <iostream>

// Custom exception class for this assignemt.
// Inherits from std::exception so it can be caught using (std::exception& e)
class MyException : public std::exception
{
   private:
    const std::string message;

   public:
    // constructor stores the error message passed in
    explicit MyException(const std::string& msg);
    // overrides std::exception what()
    virtual const char* what() const noexcept override;
};

#endif
