#ifndef SHAPEMANAGER_H
#define SHAPEMANAGER_H

#include <string>

#include "ShapeTwoD.h"
using namespace std;

extern vector<ShapeTwoD*> shapeList;
void promptShapeType();
void validateName(const string& name);
void validateSpecialType(const string& specialType);
void printShapes();
void deallocateSafely();
void updateArea();
void sortBySpecialType();
void sortAllByAreaDescending(vector<ShapeTwoD*> sortedList);
void sortAllByAreaAscending(vector<ShapeTwoD*> sortedList);
#endif
