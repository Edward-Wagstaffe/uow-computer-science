// File: citylocation.h
// Header file for the city module.

#ifndef CITYLOCATION_H
#define CITYLOCATION_H
#include <string>

using namespace std;

// populates the grid with the city numbers.
void populateGridWithCities();
// parses the city location file
void processCityData(string filename);
// safely frees memory for the city array
void deallocateCityData();
#endif
