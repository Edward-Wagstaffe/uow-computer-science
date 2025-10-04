#include "weatherSummary.h"

#include <cmath>
#include <iomanip>

#include "addedFeature.h"
#include "globals.h"
#include "weatherData.h"

// checks if the given coordinate is a city.
bool isCityPoint(int a, int b)
{
    for (int i = 0; i < cityCounter; i++)
    {
        City* city = cityDataArray[i];
        for (int j = 0; j < city->coordCount; j++)
        {
            int x = city->coordinates[j].x;
            int y = city->coordinates[j].y;

            if (x == a && y == b)
            {
                return true;
            }
        }
    }
    return false;
}

// Get city and perimeter coordinates (accounts for non-rectangular cities)
CoordinatePair* getCityAndPerimeter(int cityNumber, int& count)
{
    // Initialize an array to track included coordinates (avoid duplicates)
    bool** isIncludedGrid = new bool*[grid->rows];
    for (int i = 0; i < grid->rows; i++)
    {
        isIncludedGrid[i] = new bool[grid->cols]();
    }

    // Temporary storage for city and perimeter coordinates
    CoordinatePair* tempCoords = new CoordinatePair[grid->area];
    int tempCount = 0;

    // find the city by ID
    for (int i = 0; i < cityCounter; i++)
    {
        if (cityDataArray[i]->number == cityNumber)
        {
            City* city = cityDataArray[i];

            // add the city coordinates
            for (int j = 0; j < city->coordCount; j++)
            {
                int x = city->coordinates[j].x;
                int y = city->coordinates[j].y;
                if (!isIncludedGrid[y - grid->minY][x - grid->minX])
                {
                    isIncludedGrid[y - grid->minY][x - grid->minX] = true;
                    tempCoords[tempCount] = CoordinatePair(x, y);
                    tempCount++;
                }
            }
            // add perimeter coordinates
            for (int j = 0; j < city->coordCount; j++)
            {
                int x = city->coordinates[j].x;
                int y = city->coordinates[j].y;
                // check eight adjacent cells
                int directions[8][2] = {
                    {0, 1},  {0, -1},
                    {1, 0},  {-1, 0},  // Cardinal: up, down, right, left
                    {1, 1},  {1, -1},
                    {-1, 1}, {-1, -1}  // Diagonal: top-right, bottom-right, top-left, bottom-left
                };
                for (int (&dir)[2] : directions)
                {
                    int newX = x + dir[0];
                    int newY = y + dir[1];
                    // ensure that the perimeter is within the grid bounds and are also not city
                    // points.
                    if (newX >= grid->minX && newX <= grid->maxX && newY >= grid->minY &&
                        newY <= grid->maxY)
                    {
                        if (!isCityPoint(newX, newY) &&
                            !isIncludedGrid[newY - grid->minY][newX - grid->minX])
                        {
                            isIncludedGrid[newY - grid->minY][newX - grid->minX] = true;
                            tempCoords[tempCount] = CoordinatePair(newX, newY);
                            tempCount++;
                        }
                    }
                }
            }
            break;
        }
    }

    // Copy into final array
    count = tempCount;
    CoordinatePair* result = new CoordinatePair[count];
    for (int i = 0; i < count; i++)
    {
        result[i] = tempCoords[i];
    }

    // Clean up the temp resources
    delete[] tempCoords;
    for (int i = 0; i < grid->rows; i++)
    {
        delete[] isIncludedGrid[i];
    }
    delete[] isIncludedGrid;

    return result;
}

// calculates the given weather data's average based on the city and its perimeter
float calculateAverageWeather(CoordinatePair*& cityAndPerimeter, weatherData**& wArray)
{
    float sum = 0;
    // iterate through weather data
    for (int i = 0; i < grid->area; i++)
    {
        weatherData* wData = wArray[i];

        for (int j = 0; j < cityAndPerimeterCount; j++)
        {  // if weather coordinates match city and perimeter coordinates
            if (wData->coordinates.x == cityAndPerimeter[j].x &&
                wData->coordinates.y == cityAndPerimeter[j].y)
            {
                sum += wData->percentage;
            }
        }
    }
    float avg = sum / cityAndPerimeterCount;
    return avg;
}

// this function determines the rain probability  based on the pressure and cloud coverage symbols
int getRainProbability(string apLMH, string accLMH)
{
    if (apLMH == "L")
    {
        if (accLMH == "H")
        {
            return 90;
        }
        else if (accLMH == "M")
        {
            return 80;
        }
        else if (accLMH == "L")
        {
            return 70;
        }
    }

    else if (apLMH == "M")
    {
        if (accLMH == "H")
        {
            return 60;
        }
        else if (accLMH == "M")
        {
            return 50;
        }
        else if (accLMH == "L")
        {
            return 40;
        }
    }

    else if (apLMH == "H")
    {
        if (accLMH == "H")
        {
            return 30;
        }
        else if (accLMH == "M")
        {
            return 20;
        }
        else if (accLMH == "L")
        {
            return 10;
        }
    }
    cout << "Invalid arguements for rain getRainProbability" << endl;
    return -1;
}

// Prints beautiful ASCII art to represent the rain probability.
void printRainASCII(int rainProbability)
{
    switch (rainProbability)
    {
        case 90:
            cout << R"(~~~~
~~~~~
\\\\\
      )";
            break;
        case 80:
            cout << R"(~~~~
~~~~~
 \\\\
      )";
            break;
        case 70:
            cout << R"(~~~~
~~~~~
  \\\
      )";
            break;
        case 60:
            cout << R"(~~~~
~~~~~
   \\
      )";
            break;
        case 50:
            cout << R"(~~~~
~~~~~
    \
      )";
            break;
        case 40:
            cout << R"(~~~~
~~~~~
      )";
            break;
        case 30:
            cout << R"(~~~
~~~~
      )";
            break;
        case 20:
            cout << R"(~~
~~~
      )";
            break;
        case 10:
            cout << R"(~
~~
      )";
            break;
    }
}

// Prints weather summary report for each city and their associated cloud cover, pressure, rain
// probability and UV index (if data is loaded)
void printWeatherSummary()
{
    cout << "Weather Forecast Summary Report" << endl;
    cout << "-------------------------------" << endl;
    ;
    for (int i = 0; i < cityCounter; i++)
    {
        City* city = cityDataArray[i];
        string cityName = city->name;
        int cityNumber = city->number;
        // get city and perimeter coordinates
        CoordinatePair* cityAndPerimeter = getCityAndPerimeter(cityNumber, cityAndPerimeterCount);
        // calculate average cloud cover and pressure
        float acc = calculateAverageWeather(cityAndPerimeter, cloudDataArray);
        float ap = calculateAverageWeather(cityAndPerimeter, pressureDataArray);
        // convert to LMH symbols
        string accLMH = convertPercentageToSymbol(acc);
        string apLMH = convertPercentageToSymbol(ap);
        // calculate rain probability
        int rainProbability = getRainProbability(apLMH, accLMH);

        // print the formatted summary (with reference to the A1 outline)
        cout << fixed << setprecision(2);
        cout << left << setw(10) << "City Name " << ": " << cityName << endl;
        cout << left << setw(10) << "City ID " << ": " << cityNumber << endl;
        cout << left << setw(25) << "Ave. Cloud Cover (ACC) " << ": " << acc << " (" << accLMH
             << ")" << endl;
        cout << left << setw(25) << "Ave. pressure (AP) " << ": " << ap << " (" << apLMH << ")"
             << endl;
        cout << left << setw(25) << "Probability of Rain (%) " << ": " << rainProbability << endl;
        printRainASCII(rainProbability);
        cout << endl;
        // Include UV index if elevaton data is loaded.
        if (elevationDataArray != nullptr)
        {
            float UVIndex = calculateAverageUVIndex(cityAndPerimeter);
            cout << setw(10) << "Ave. UV Index " << ": " << round(UVIndex) << " ";
            printUVIndexASCII(UVIndex);
        }
        cout << endl << endl;
        delete[] cityAndPerimeter;  // free allocated coordinates
    }
    cout << endl << endl;
}
