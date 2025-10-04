// File: utils.h

#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

// gets the current system month
int getSystemMonth();
// checks whether a string starts with the given prefix
bool startsWith(const string &str, const string &prefix);
// splits the string  into tokens based on the delimeter
vector<string> tokenizeString(string input, string delimiter);
// trims leading and trailing whitespace from a string.
string trim(const string &str);

#endif
