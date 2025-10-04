// File: cityStruct.h
// Defines the city struct  for storing the citys ID,  name and coordinates.
#ifndef CITYSTRUCT_H
#define CITYSTRUCT_H

#include <string>

#include "coordinatesStruct.h"

using namespace std;

using std::string;

struct City
{
    int number;                   // unique city ID
    string name;                  // City name
    CoordinatePair* coordinates;  // dynamic array of coordinates.
    int coordCount;               // current coordinate count
    int coordCapacity;            // current coordinate capacity

    // Initializes a city with a number , name and initial coords.
    City(int num, const string& n, int x, int y);
    // Deconstructor that frees coordinates array.
    ~City();

    // Adds a coordinate to the city, resizing the array if needed.
    void addCoordinate(int x, int y);
};

#endif
