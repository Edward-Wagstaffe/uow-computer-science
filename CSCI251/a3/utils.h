// file: utils.h

#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>
#include <vector>

// splits the string  into tokens based on the delimeter
std::vector<std::string> tokenizeString(std::string input, std::string delimiter);
// trims leading and trailing whitespace from a string.
std::string trim(const std::string &str);

// type conversion templates
template <typename T>
T convertFrStringToPrimitiveType(std::string input)
{
    std::istringstream iss(input);
    T output;
    iss >> output;
    return output;
}

template <typename T>
std::string convertFrPrimitiveTypeToString(T input)
{
    std::ostringstream oss;
    oss << input;  // fixed from 'output' to 'input'
    return oss.str();
}

#endif
