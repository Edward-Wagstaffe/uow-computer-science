// File: globals.h

#ifndef GLOBALS_H
#define GLOBALS_H

#include "cityStruct.h"
#include "gridStruct.h"
#include "weatherDataStruct.h"

extern Grid *grid;

extern City **cityDataArray;
extern int cityCounter;

extern weatherData **cloudDataArray;
extern weatherData **pressureDataArray;
extern weatherData **elevationDataArray;

extern int cityAndPerimeterCount;

extern bool configLoaded;
extern bool elevationLoaded;

#endif
