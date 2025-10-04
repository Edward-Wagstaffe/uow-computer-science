// File: menu.h
#ifndef MENU_H
#define MENU_H

// Shows the menu
void displayMenuOptions();
// Resets the system, prompts user for config file, processes it and initializes structs.
void handleConfig();
// Prints grid with cities
void handleDisplayCity();
// Prints grid with cloud coverage index
void handleDisplayCloudIndex();
// prints grid with pressure index
void handleDisplayPressureIndex();
// prints grid with pressure symbols (LMH)
void handleDisplayPressureSymbol();
// prints grid with cloud symbols (LMH)
void handleDisplayCloudSymbol();
// Prints out the weather summary
void handleWeatherSummary();
// prints grid with elevation data
void handleDisplayElevation();
// prints grid with UV data
void handleDisplayUVIndex();
// randomly generates elevation
void handleGenerateElevationFile();
// Enter confirmation before returning to the menu
void pressEnterToContinue();
#endif
