#include "configHandler.h"

#include <fstream>
#include <sstream>

#include "citylocation.h"
#include "globals.h"
#include "utils.h"
#include "weatherData.h"

/* This function reads the config file line by line. Each line corresponds to a
 * specific piece of information:
 * line 1: X-range
 * line 2: Y-range
 * line 3: City location file
 * line 4: Cloud coverage file
 * line 5: Pressure file
 *
 * A grid is initilized based on the ranges and the file data are stored into
 * their respective structs.
 *
 * One of the assumptions made after disregarding comments and empty lines,
 * is that the config file has exactly 5 lines of interest.
 */
void parseConfigFile(string filename)
{
    filename = trim(filename);
    // open the configuration file
    fstream inputFile(filename.c_str(), fstream::in);
    string aLine;
    int minX, maxX, minY, maxY;

    int dataLine = 0;
    while (getline(inputFile, aLine))

    {  // Trim leading and trailing whitespaces from the line
        aLine = trim(aLine);
        // Skip comments and empty lines.
        if (startsWith(aLine, "//") || aLine == "")
        {
            continue;
        }

        dataLine++;
        switch (dataLine)
        {
            case 1:
            {
                // parse the X-range
                vector<string> tokens = tokenizeString(aLine, "=");
                tokens = tokenizeString(tokens[1], "-");
                istringstream issMin(tokens[0]);
                issMin >> minX;
                istringstream issMax(tokens[1]);
                issMax >> maxX;
                cout << endl;
                cout << "Reading in GridX_IdxRange: " << minX << "-" << maxX << " ... done!"
                     << endl;
                break;
            }
            case 2:
            {
                // parse the Y-range
                vector<string> tokens = tokenizeString(aLine, "=");
                tokens = tokenizeString(tokens[1], "-");
                istringstream issMin(tokens[0]);
                issMin >> minY;
                istringstream issMax(tokens[1]);
                issMax >> maxY;

                // Iniitalize the 2D array based on the ranges.
                grid = new Grid(minX, maxX, minY, maxY);
                cout << "Reading in GridY_IdxRange: " << minY << "-" << maxY << " ... done!"
                     << endl;
                break;
            }
            case 3:
            {
                cout << endl;
                cout << "Storing data from input file: " << endl;

                // Process the city data
                processCityData(aLine);
                cout << aLine << " ... done!" << endl;
                break;
            }
            case 4:
            {
                // Process the cloud coverage data
                processWeatherData(aLine, cloudDataArray);

                cout << aLine << " ... done!" << endl;
                break;
            }
            case 5:
            {
                // Process the pressure data
                processWeatherData(aLine, pressureDataArray);
                cout << aLine << " ... done!" << endl << endl;
                break;
            }
            case 6:
            {
                cout << "There are more data than expected." << endl;
                break;
            }
        }
    }
    if (dataLine == 5)
    {
        configLoaded = true;  // Mark config as successfully loaded.
        cout << endl;
        cout << "All records successfully stored.\nGoing back to main menu ..." << endl;
    }
    else
    {
        cout << endl;
        cout << "Error: Something went wrong please try again." << endl;
    }
    inputFile.close();
}

// Frees memory safely
void deallocateAndReset()
{
    if (configLoaded)  // check if configuration data is loaded.
    {
        grid->~Grid();                             // Explicitly call the grid deconstructor
        deallocateCityData();                      // free city data
        cityCounter = 0;                           // reset city counter
        deallocateWeatherData(cloudDataArray);     // free cloud data
        deallocateWeatherData(pressureDataArray);  // free pressure data
        configLoaded = false;                      // reset config flag
    }
    if (elevationLoaded)
    {
        deallocateWeatherData(elevationDataArray);  // free elevation data
        elevationLoaded = false;                    // reset elevation flag
    }
}
