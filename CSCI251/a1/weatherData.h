#ifndef WEATHER_H
#define WEATHER_H

#include <string>

#include "weatherDataStruct.h"

using namespace std;

// parses the a weather data file.
void processWeatherData(string filename, weatherData **&weatherArray);
// frees dynamically allocated memory of the weather data
void deallocateWeatherData(weatherData **&array);
void populateGridWithSymbolData(weatherData **&array);
int convertPercentageToIndex(int percentage);
string convertPercentageToSymbol(int percentage);
void populateGridWithIndexData(weatherData **&array);
string convertPercentageToSymbol(float percentage);

#endif
