#ifndef PROCESSIOFILE_H
#define PROCESSIOFILE_H
#include <iostream>
#include <vector>

#include "ConnectedLine2D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "Point2D.h"
#include "Point3D.h"

void parseFile(std::string filename);
void processPoint3D(std::string &xVal, std::string &yVal, std::string &zVal);
void processPoint2D(std::string &xVal, std::string &yVal);
void processLine2D(std::string &xVal1, std::string &yVal1, std::string &xVal2, std::string &yVal2);
void processLine3D(std::string &xVal1, std::string &yVal1, std::string &zVal1, std::string &xVal2,
                   std::string &yVal2, std::string &zVal2);
void processConnectedLine2D(std::string &xVal1, std::string &yVal1, std::string &midxVal,
                            std::string &midyVal, std::string &xVal2, std::string &yVal2);

extern std::vector<Point2D> point2dArray;
extern std::vector<Line2D> line2dArray;
extern std::vector<Point3D> point3dArray;
extern std::vector<Line3D> line3dArray;
extern std::vector<ConnectedLine2D> cLine2dArray;

extern bool fileLoaded;

void generateOutputFile(std::string filename);
#endif
