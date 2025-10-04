
#include "cityStruct.h"

City::City(int num, const string& n, int x, int y)
    : number(num), name(n), coordinates(nullptr), coordCount(0), coordCapacity(1)
{
    coordinates =
        new CoordinatePair[coordCapacity];  // allocate initial space for 1 pair of coordinates
    coordinates[0] = {x, y};                // Store inital coordinates
    coordCount = 1;                         // update coords counter to 1
}

// Dynamically frees the allocated coordinates array.
City::~City()
{
    delete[] coordinates;
}

// Adds new coordinates to the city and dynamically resizes array if needed.
void City::addCoordinate(int x, int y)
{
    if (coordCount >= coordCapacity)  // check if the array needs resizings
    {
        coordCapacity *= 2;                                        // double capacity
        CoordinatePair* temp = new CoordinatePair[coordCapacity];  // allocate the new array

        for (int i = 0; i < coordCount; ++i)
        {
            temp[i] = coordinates[i];  // copy existing coordinates to new array
        }

        delete[] coordinates;  // deallocate old array
        coordinates = temp;    // point to new array
    }

    coordinates[coordCount] = {x, y};  // add the new coordinates
    coordCount++;
}
