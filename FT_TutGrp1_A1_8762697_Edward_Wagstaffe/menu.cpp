
#include "menu.h"

#include <iomanip>
#include <iostream>

#include "addedFeature.h"
#include "citylocation.h"
#include "configHandler.h"
#include "globals.h"
#include "weatherData.h"
#include "weatherSummary.h"

using namespace std;

// Displays the main menu for the WIP.
// Includes min requirement options 1-7 for configurations and data display
// plus added features 8-10 for elevation and UV index display.
void displayMenuOptions()
{
    cout << left << setw(15) << "Student ID " << ": " << "8762697" << endl;
    cout << left << setw(15) << "Student Name:" << ": " << "Edward Wagstaffe" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Welcome to Weather Information Processing System!" << endl << endl;
    cout << "1) Read in and process a configuration file" << endl;
    cout << "2) Display city map" << endl;
    cout << "3) Display cloud coverage map(cloudiness index)" << endl;
    cout << "4) Display cloud coverage map(LMH symbols)" << endl;
    cout << "5) Display atmospheric pressure map(pressure index)" << endl;
    cout << "6) Display atmospheric pressure map(LMH symbols)" << endl;
    cout << "7) Show weather forecast summary report" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "             Added features              " << endl;
    cout << "8) Generate and process 'elevation.txt'" << endl;
    cout << "9) Display elevation map (1-low, 5-high)" << endl;
    cout << "10) Calculate and display UV index" << endl;
    cout << "11) Quit " << endl << endl;

    cout << "Please enter your choice (1-11) : ";
}

// handles option 1: reads in a processes the config file.
void handleConfig()
{
    deallocateAndReset();  // clears existing configuration and data
    cout << endl;
    cout << "[Read in and process a configuration file]" << endl;
    cout << "Please enter config filename : ";
    string configFile;
    cin >> configFile;            // read the config file
    parseConfigFile(configFile);  // process the config file
    cout << endl << endl;
}

// handles option 2: Which displays the city map on the grid.
// Requires configLoaded to be true, clears existing grid data and populates with city data.
void handleDisplayCity()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Display city map]" << endl;
        grid->clear2DArray();         // reset grid data.
        populateGridWithCities();     // populate with city location
        cout << grid->displayGrid();  // display the grid.
    }
    else
    {
        cout << "Error: No data found please load a configuration file -> Menu option (1)" << endl;
    }
}

// handles option 3: displays a cloud coverage map using indicies.
// requires configLoaded to be true. clears exisitng grid data and populates with inidicies.
void handleDisplayCloudIndex()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Display cloud coverage map (cloudiness index)]" << endl;
        grid->clear2DArray();                       // reset grid data
        populateGridWithIndexData(cloudDataArray);  // populate with cloud indicies
        cout << grid->displayGrid();                // display the grid
    }
    else
    {
        cout << "Error: No data found please load a configuration file -> Menu option (1)" << endl;
    }
}

// handles option 4:  displays a cloud coverage map using low, medium and high (LMH) symbols
// requires configloaded to be true, clears existing grid data and populates with associated
// symbols.
void handleDisplayCloudSymbol()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Display cloud coverage map (LMH symbols)]" << endl;
        grid->clear2DArray();
        populateGridWithSymbolData(cloudDataArray);
        cout << grid->displayGrid();
    }
    else
    {
        cout << "Error: No data found please load a configuration file -> Menu option (1)" << endl;
    }
}

// handles option 5: displays pressure map using indicies.
// requires configloaded to be true, clears existing grid data and populates with indicies.
void handleDisplayPressureIndex()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Display atmospheric pressure map (pressure index)]" << endl;
        grid->clear2DArray();
        populateGridWithIndexData(pressureDataArray);
        cout << grid->displayGrid();
    }
    else
    {
        cout << "Error: No data found please load a configuration file -> Menu option (1)" << endl;
    }
}

// handles option 6: displays the pressure map using low, medium and high (LMH) symbols
// requires configloaded to be true, clears existing grid data and populates with associated
// symbols.
void handleDisplayPressureSymbol()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Display atmospheric pressure map (LMH symbols)]" << endl;
        grid->clear2DArray();
        populateGridWithSymbolData(pressureDataArray);
        cout << grid->displayGrid();
    }
    else
    {
        cout << "Error: No data found please load a configuration file -> Menu option (1)" << endl;
    }
}

// handles option 7: Displays a weather forecast summary report.
// requires configloaded to be true.
void handleWeatherSummary()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Show weather forecast summary report]" << endl << endl;
        printWeatherSummary();
    }
    else
    {
        cout << "Error: No data found please load a configuration file -> Menu option (1)" << endl;
    }
}

// handles option 8: generates and processes an elevation file as if it were given by the API.
// after processing it sets the elevationLoaded flag to true.
void handleGenerateElevationFile()
{
    cout << endl;
    if (configLoaded)
    {
        cout << endl;
        cout << "[Generate and process 'elevation.txt']" << endl;
        generateElevationFile();  // generate random elevation for each coordinate.
        processWeatherData("elevation.txt", elevationDataArray);
        elevationLoaded = true;  // set flag to true.
        cout << "The file 'elevation.txt' has been randomly generated \nto simulate data provided "
                "by "
                "the "
                "weather station."
             << endl;
    }
    else
    {
        cout << "Error: Please load a configuration file first. -> "
                "Menu option (1) "
             << endl;
    }
}

// handles option 9: displays an elevation map with values (1-low, 5-high)
// requires both configloaded and elevationloaded to be true. Clears existing grid and populates
// with elevation data.
void handleDisplayElevation()
{
    cout << endl;
    if (configLoaded && elevationLoaded)
    {
        cout << endl;
        cout << "[Display elevation map (1-low, 5-high)]" << endl << endl;
        grid->clear2DArray();
        populateGridWithElevation(elevationDataArray);
        cout << grid->displayGrid();
    }
    else
    {
        cout << "Error: Please ensure both config file and elevation file dat are loaded  -> "
                "Menu option (1) and (8) respectively."
             << endl;
    }
}

// handles option 10: calculates and displays UV index on the map.
// requires both configloaded and elevationloaded, clears existing grid and populates with UV index
// data.
void handleDisplayUVIndex()
{
    cout << endl;
    if (configLoaded && elevationLoaded)
    {
        cout << endl;
        cout << "[Calculate and display UV index]" << endl;
        grid->clear2DArray();
        populateGridWithUVIndex(cloudDataArray);
        cout << grid->displayGrid();
    }
    else
    {
        cout << "Error: Please ensure both config file and elevation file dat are loaded  -> "
                "Menu option (1) and (8) respectively."
             << endl;
    }
}

// Prompts user to press eneter to return to main menu.
// Clears input buffer and ensures only <enter> is accepted.
void pressEnterToContinue()
{
    // clears any previous input from the input buffer
    cin.ignore(50, '\n');
    string userInput;

    // Continuously prompts user to press Enter.
    do
    {
        cout << "\nPress <Enter> to go back to main menu";
        getline(cin, userInput);
    } while (userInput.length() != 0);
    cout << endl;
}
