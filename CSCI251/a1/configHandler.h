// File: configHandler.h
// Header file for the config parser and memory safety.

#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <string>
using namespace std;
// cleans up and processes the config file line by line and initializes structs.
void parseConfigFile(string filename);
// Frees memory safely and resets some global variables.
void deallocateAndReset();
#endif
