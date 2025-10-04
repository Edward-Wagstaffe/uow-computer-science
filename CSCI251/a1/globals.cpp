#include "globals.h"

// Pointer to the City objects
City **cityDataArray = nullptr;
// Pointer to the weatherData object representing cloud coverage data
weatherData **cloudDataArray = nullptr;
// Pointer to the weatherData object representing pressure data
weatherData **pressureDataArray = nullptr;
// Flag that indicates whether config file was sucessfully loaded.
bool configLoaded = false;
// Counts the number of cities in the cityDataArray
int cityCounter = 0;
// Counts the number of city points and their perimeter
int cityAndPerimeterCount = 0;
// Pointer to the weatherData object representing elevation data.
weatherData **elevationDataArray = nullptr;
// Flag that indicates whether the elevation data has been sucessfuly loaded
bool elevationLoaded = false;
// Pointer to the Grid object that defines the 2D array grid.
Grid *grid = nullptr;
