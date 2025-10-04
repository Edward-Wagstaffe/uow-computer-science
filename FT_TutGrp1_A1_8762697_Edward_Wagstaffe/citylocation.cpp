#include "citylocation.h"

#include <fstream>
#include <sstream>

#include "cityStruct.h"
#include "globals.h"
#include "utils.h"
/*This function reads the city location file, parses each line and stores the city
 * information in an array of City structs.
 *
 * Each line is expected to be in the same format e.g "[x, y]-cityNumber-cityName "
 *
 * It handles resizing of the array if more cities are found than initially allocated
 * */
void processCityData(string filename)
{
    fstream inputFile(filename.c_str(), fstream::in);
    string aLine;
    int capacity = 10;
    cityDataArray = new City *[capacity];

    while (getline(inputFile, aLine))
    {
        // Trim leading and trailing whitespaces from the line
        aLine = trim(aLine);
        // Skip comments and empty lines.
        if (startsWith(aLine, "//") || aLine == "")
        {
            continue;
        }

        // tokenize the line: "[1, 1]-3-Big_City" -> [["1,1"], "3", "Big_city"]
        vector<string> tokens = tokenizeString(aLine, "-");
        // first token should be [0, 8] for example
        string coordinatesToken = tokens[0];
        // remove brackets
        coordinatesToken = coordinatesToken.substr(1, coordinatesToken.size() - 2);
        // split into x and y
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

        int cityNumber;
        istringstream iss(tokens[1]);
        iss >> cityNumber;
        string cityName = tokens[2];

        bool found = false;
        // check if the city already exists in the array
        for (int i = 0; i < cityCounter; i++)
        {
            if (cityDataArray[i]->number == cityNumber && cityDataArray[i]->name == cityName)
            {
                // If found, add the new coordinates to the existing city.
                cityDataArray[i]->addCoordinate(x, y);
                found = true;
                break;
            }
        }

        // if not found, add a new city to the array.
        if (!found)
        {
            // check if we need to resize to array
            if (cityCounter >= capacity)
            {
                // double the capacity
                capacity *= 2;
                // allocate new array with increrased capacity
                City **temp = new City *[capacity];
                for (int i = 0; i < cityCounter; i++)
                {
                    // copy data
                    temp[i] = cityDataArray[i];
                }
                // deallocate the old array of pointers
                delete[] cityDataArray;
                // update pointer to new array.
                cityDataArray = temp;
            }

            // create new city object
            cityDataArray[cityCounter] = new City(cityNumber, cityName, x, y);
            cityCounter++;
        }
    }
    inputFile.close();
}
// populates the grid with the city numbers.
void populateGridWithCities()
{
    for (int i = 0; i < cityCounter; i++)
    {
        City *city = cityDataArray[i];
        for (int j = 0; j < city->coordCount; j++)
        {
            int x = city->coordinates[j].x;
            int y = city->coordinates[j].y;

            ostringstream oss;
            oss << city->number;
            grid->array2D[y - grid->minY][x - grid->minX] = oss.str();  // Use offset
        }
    }
}

// safely frees memory for the city array
void deallocateCityData()
{
    for (int i = 0; i < cityCounter; i++)
    {
        delete cityDataArray[i];
    }
    delete[] cityDataArray;
    cityDataArray = nullptr;
    cout << "deallocated cityData" << endl;
}
