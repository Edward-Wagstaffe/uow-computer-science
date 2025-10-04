// File: weatherDataStruct.h

#ifndef WEATHERDATASTRUCT_H
#define WEATHERDATASTRUCT_H

#include <iostream>

#include "coordinatesStruct.h"

using namespace std;

// Struct that can represent any weather data at a specific coordinate
// can be used for cloud cover, pressure and elevation or any future weather data in this format.
struct weatherData
{
    int percentage;              // value of the weather data
    CoordinatePair coordinates;  // coordinates where the weather value applies

    // non default constructor
    weatherData(int num, int xVal, int yVal) : coordinates(xVal, yVal)
    {
        percentage = num;
    }
};

#endif
