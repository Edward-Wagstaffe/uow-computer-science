#ifndef WEATHERSUMMARY_H
#define WEATHERSUMMARY_H

#include <string>

#include "coordinatesStruct.h"
#include "weatherDataStruct.h"

using namespace std;

// checks if the given coordinate is a city.
bool isCityPoint(int a, int b);
// Get city and perimeter coordinates (accounts for non-rectangular cities)
CoordinatePair* getCityAndPerimeter(int cityNumber, int& count);
// calculates the given weather data's average based on the city and its perimeter
float calculateAverageWeather(CoordinatePair*& cityAndPerimeter, weatherData**& wArray);
// displays the weather summary report
void printWeatherSummary();
// gets the probability of rain based on pressure and cloud cover LMH symbols
int getRainProbability(string apLMH, string accLMH);
void printRainASCII(int rainProbability);

#endif
