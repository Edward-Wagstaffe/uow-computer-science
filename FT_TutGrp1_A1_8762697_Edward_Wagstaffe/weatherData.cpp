#include "weatherData.h"

#include <fstream>
#include <sstream>

#include "globals.h"
#include "utils.h"

/*This function reads the weather data file, parses each line and stores the weather
 * info in the weatherData struct.
 *
 * Each line is expected to be in the format e.g. [x, y]-percentage.
 *
 *It also handles resizing of the array if more data are found that initially initialized.
 */
void processWeatherData(string filename, weatherData **&weatherArray)
{
    fstream inputFile(filename.c_str(), fstream::in);
    string aLine;

    int capacity = 10;
    int count = 0;
    weatherArray = new weatherData *[capacity];

    while (getline(inputFile, aLine))
    {
        // Trim leading and trailing whitespaces from the line
        aLine = trim(aLine);
        // Skip comments and empty lines.
        if (startsWith(aLine, "//") || aLine == "")
        {
            continue;
        }
        vector<string> tokens = tokenizeString(aLine, "-");
        string coordinatesToken = tokens[0];
        coordinatesToken = coordinatesToken.substr(1, coordinatesToken.size() - 2);
        vector<string> coords = tokenizeString(coordinatesToken, ", ");
        int x;
        istringstream issX(coords[0]);
        issX >> x;
        int y;
        istringstream issY(coords[1]);
        issY >> y;

        // check whether (x, y) is within the grid ranges
        if (!(x >= grid->minX && x <= grid->maxX && y >= grid->minY && y <= grid->maxY))
        {
            continue;  // skip out of range.
        }
        int percentage;
        istringstream issP(tokens[1]);
        issP >> percentage;

        if (count >= capacity)
        {
            capacity *= 2;
            weatherData **temp = new weatherData *[capacity];
            for (int i = 0; i < count; i++) temp[i] = weatherArray[i];
            delete[] weatherArray;
            weatherArray = temp;
        }

        weatherArray[count] = new weatherData(percentage, x, y);
        count++;
    }

    inputFile.close();
}

/*This function deallocates the memory used by the cityDataArray.
 * Deletes each city object first, and then the array itself.*/

/*This function deallocates the memory used by any of the weatherData arrays.
 * Deletes each weatherData object first, and then the array itself.*/
void deallocateWeatherData(weatherData **&array)
{
    for (int i = 0; i < grid->area; i++)
    {
        delete array[i];
    }
    delete[] array;
    array = nullptr;
    cout << "deallocated weatherData" << endl;
}

void populateGridWithIndexData(weatherData **&array)
{
    for (int i = 0; i < grid->area; i++)
    {
        weatherData *wData = array[i];
        int weatherIndex = convertPercentageToIndex(wData->percentage);

        int x = wData->coordinates.x;
        int y = wData->coordinates.y;

        ostringstream oss;
        oss << weatherIndex;
        grid->array2D[y - grid->minY][x - grid->minX] = oss.str();  // Use offset
    }
}

int convertPercentageToIndex(int percentage)
{
    if (percentage < 0)
    {
        cout << "Invalid percentage, must not be a negative number: returning -1" << endl;
        return -1;
    }
    switch (percentage / 10)
    {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 6:
            return 6;
        case 7:
            return 7;
        case 8:
            return 8;
        case 9:
            return 9;
        default:
            cout << "Invalid percentage, must not exceed 100: returning -2" << endl;
            return -2;
    }
}

string convertPercentageToSymbol(int percentage)
{
    if (percentage < 0)
    {
        cout << "Invalid percentage, must not be a negative number." << endl;
        return "";
    }
    else if (percentage < 35)
    {
        return "L";
    }
    else if (percentage < 65)
    {
        return "M";
    }
    else if (percentage < 100)
    {
        return "H";
    }
    else
    {
        cout << "Invalid percentage, must not exceed 100" << endl;
        return "";
    }
}

void populateGridWithSymbolData(weatherData **&array)
{
    // Clear array first to avoid stale data

    for (int i = 0; i < grid->area; i++)
    {
        weatherData *wData = array[i];
        string weatherSymbol = convertPercentageToSymbol(wData->percentage);

        int x = wData->coordinates.x;
        int y = wData->coordinates.y;

        ostringstream oss;
        oss << weatherSymbol;
        grid->array2D[y - grid->minY][x - grid->minX] = oss.str();  // Use offset
    }
}

string convertPercentageToSymbol(float percentage)
{
    if (percentage < 0)
    {
        cout << "Invalid percentage, must not be a negative number." << endl;
        return "";
    }
    else if (percentage < 35)
    {
        return "L";
    }
    else if (percentage < 65)
    {
        return "M";
    }
    else if (percentage < 100)
    {
        return "H";
    }
    else
    {
        cout << "Invalid percentage, must not exceed 100" << endl;
        return "";
    }
}
