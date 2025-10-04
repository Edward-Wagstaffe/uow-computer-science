#ifndef SORTING_H
#define SORTING_H

#include <iostream>

void sortAndDisplayData();
void sortPoint2D();
void sortPoint3D();
void sortLine2D();
void sortLine3D();
void sortConnectedLine2D();

std::string getPoint2DString();
std::string getPoint3DString();
std::string getLine2DString();
std::string getLine3DString();
std::string getConnectedLine2DString();

void generateOutputFile(std::string filename);

#endif
