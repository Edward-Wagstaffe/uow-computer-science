// File: coordinatesStruct.h

#ifndef COORDINATESSTRUCT_H
#define COORDINATESSTRUCT_H

// represents coordinates on a grid.
// used for city locations, weather data locations, perimeter points.
struct CoordinatePair
{
    int x;
    int y;

    CoordinatePair() {}
    // initializes coordinates  with given values..
    CoordinatePair(int xVal, int yVal)
    {
        x = xVal;
        y = yVal;
    }
};

#endif
