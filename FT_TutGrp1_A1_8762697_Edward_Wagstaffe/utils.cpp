#include "utils.h"

#include <chrono>
#include <ctime>

// checks whether a string starts with the given prefix
bool startsWith(const string &str, const string &prefix)
{
    return str.compare(0, prefix.length(), prefix) == 0;
}

// splits the string  into tokens based on the delimeter
vector<string> tokenizeString(string input, string delimiter)
{
    size_t pos = 0;  // declare pos of type size_t (unsigned long) and assign to 0.
    string token;
    vector<string> result;

    while ((pos = input.find(delimiter)) !=
           string::npos)  // While we are able to find the delimiter within the string
    {
        token = input.substr(0, pos);              // from index 0, take pos(index) characters
        result.push_back(token);                   // push it to the dynamic array
        input.erase(0, pos + delimiter.length());  // erase that token plus delimiter
    }

    result.push_back(input);  // push the remainder of the string which is the final token.

    return (result);
}

// trims leading and trailing whitespace from a string.
string trim(const string &str)
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

// gets the current system month (0 = January, 11 = December)
int getSystemMonth()
{
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Convert to local time structure
    tm *local_time = localtime(&now_time);

    int month = local_time->tm_mon;
    return month;
}
