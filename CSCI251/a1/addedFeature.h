// File: addedFeature.h
// Header file for my added feature.

#ifndef ADDEDFEATURE_H
#define ADDEDFEATURE_H

#include "coordinatesStruct.h"
#include "weatherDataStruct.h"

// this function returns a season factor based on the given month to adjust UV calculations.
float getSeasonFactor(int month);
// Generates a random elevation  value between 1-5 where 1 = lowest, 5 = highest
int generateElevationValue();
// creates a file "elevation.txt" with elevation values for each coordinate
void generateElevationFile();
// This function calculates the UV index based on the season, elevation and cloud cover.
float calculateUVIndex(int month, int elevation, int cloudCover);
// This function calculates the average UV index for each city and perimeter
float calculateAverageUVIndex(CoordinatePair *&cityAndPerimeter);
// Prints the ASCII representation of various UV index levels.
void printUVIndexASCII(int UVIndex);
// Populates the grid with elevation data.
void populateGridWithElevation(weatherData **&array);
// Populates the grid with UV index data.
void populateGridWithUVIndex(weatherData **&cloudArray);
#endif
