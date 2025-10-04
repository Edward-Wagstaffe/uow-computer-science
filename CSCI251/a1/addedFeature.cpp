#include "addedFeature.h"

#include <cmath>
#include <fstream>
#include <random>
#include <sstream>

#include "globals.h"
#include "utils.h"

// this function returns a season factor based on the given month to adjust UV calculations.
// Where 0 = January, 11 = December
// I'm assuming the cities are in the northern hemisphere for this.
float getSeasonFactor(int month)
{
    if (month == 2 || month == 3 || month == 10 || month == 11)  // Spring and fall.
    {
        return 0.5;  // lower uv factor
    }
    else if (month == 4 || month == 5)  // early summer
    {
        return 0.7;  // moderate uv factor
    }
    else if (month == 6 || month == 7)  // peak summer
    {
        return 0.9;  // highest uv factor
    }
    else if (month == 8 || month == 9)  // late summer
    {
        return 0.8;  // moderate uv factor
    }
    else  // winter
    {
        return 0.2;  // minimal uv factor
    }
}

// Generates a random elevation  value between 1-5 where 1 = lowest, 5 = highest
int generateElevationValue()
{
    default_random_engine engine(random_device{}());  // seed the engine
    uniform_int_distribution<int> dist(1, 5);         // set the range 1-5

    int elevation = dist(engine);  // Generate the random elevation

    return elevation;
}

// creates a file "elevation.txt" with elevation values for each coordinate (similar to that of
// cloudCover and pressure).
void generateElevationFile()
{
    fstream outputFile("elevation.txt", fstream::out);  // open file for writing.

    for (int i = grid->minY; i < (grid->rows + grid->minY); i++)  // iterate over grid coordinates
    {
        for (int j = grid->minX; j < (grid->cols + grid->minX); j++)
        {
            int elevationValue = generateElevationValue();  // get random elevation value
            outputFile << "[" << j << ", " << i << "]" << "-" << elevationValue << endl;
        }
    }
    outputFile.close();
}

// This function calculates the UV index based on the season, elevation and cloud cover.
float calculateUVIndex(int month, int elevation, int cloudCover)
{
    int baseUV = 9;
    float seasonFactor = getSeasonFactor(month);

    float elevationFactor = 1.0 + 0.15f * (elevation - 1);                    // get seasonal factor
    float cloudModifier = 1.0f - (cloudCover / 100.0f) * 0.75f;               // get cloud modifier
    float UVIndex = baseUV * elevationFactor * seasonFactor * cloudModifier;  // calculate

    return UVIndex;
}

// This function calculates the average UV index for each city and perimeter (same as avg cloud
// cover and avg pressure)
float calculateAverageUVIndex(CoordinatePair *&cityAndPerimeter)
{
    populateGridWithUVIndex(cloudDataArray);  // First populate grid with UV indicies
    float sum = 0;
    for (int i = 0; i < cityAndPerimeterCount; i++)
    {
        float value;
        // extract the UV index at the city and perimeter coordinates.
        istringstream iss(grid->array2D[(cityAndPerimeter[i].y) - grid->minY]
                                       [(cityAndPerimeter[i].x) - grid->minX]);
        iss >> value;
        sum += value;  // accumulate the UV values.
    }

    float avg = sum / cityAndPerimeterCount;  // calculate average
    return avg;
}

// Prints the ASCII representation of various UV index levels.
void printUVIndexASCII(int UVIndex)
{
    if (UVIndex <= 2)
    {
        cout << "[==        ] Low" << endl;
    }
    else if (UVIndex <= 5)
    {
        cout << "[=====     ] Moderate" << endl;
    }
    else if (UVIndex <= 7)
    {
        cout << "[=======   ] High" << endl;
    }
    else if (UVIndex <= 10)
    {
        cout << "[==========] Very High" << endl;
    }
    else
    {
        cout << "[===========] Extreme" << endl;
    }
}

// Populates the grid with UV index data.
void populateGridWithUVIndex(weatherData **&cloudArray)
{
    populateGridWithElevation(elevationDataArray);  // Initialize grid with elevation data

    int month = getSystemMonth();  // Get current month for season factor
    for (int i = 0; i < grid->area; i++)
    {
        weatherData *cloudData = cloudArray[i];
        int x = cloudData->coordinates.x;
        int y = cloudData->coordinates.y;

        int elevation;
        // extract elevation from the grid
        istringstream iss(grid->array2D[y - grid->minY][x - grid->minX]);
        iss >> elevation;
        int cloudCover = cloudData->percentage;  // get the cloud cover percentage
        float UVIndex = calculateUVIndex(month, elevation, cloudCover);  // calculate uv index

        ostringstream oss;
        oss << round(UVIndex);                                      // rounds float to nearest int
        grid->array2D[y - grid->minY][x - grid->minX] = oss.str();  // store in grid.
    }
}

// Populates the grid with elevation data.
void populateGridWithElevation(weatherData **&array)
{
    {
        for (int i = 0; i < grid->area; i++)
        {
            weatherData *wData = array[i];

            int x = wData->coordinates.x;
            int y = wData->coordinates.y;

            ostringstream oss;
            oss << wData->percentage;
            grid->array2D[y - grid->minY][x - grid->minX] = oss.str();  // store in grid
        }
    }
}
