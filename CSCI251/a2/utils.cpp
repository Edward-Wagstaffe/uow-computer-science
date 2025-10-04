
#include "utils.h"

#include <algorithm>
#include <cctype>

// returns the capitalized string
string toUpper(const string& input)
{
    string result = input;
    transform(result.begin(), result.end(), result.begin(),
              [](unsigned char c) { return toupper(c); });
    return result;
}

// trims leading and trailing whitespace from a string.
string trim(const string& str)
{
    size_t start = 0;
    while (start < str.size() && isspace(static_cast<unsigned char>(str[start])))
    {
        ++start;
    }

    if (start == str.size())
    {
        return "";
    }

    size_t end = str.size() - 1;
    while (end > start && isspace(static_cast<unsigned char>(str[end])))
    {
        --end;
    }

    return str.substr(start, end - start + 1);
}
