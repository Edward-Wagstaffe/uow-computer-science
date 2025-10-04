#include "processIOFile.h"

#include <algorithm>
#include <fstream>
#include <string>

#include "ConnectedLine2D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Sorting.h"
#include "exceptionClass.h"
#include "menu.h"
#include "utils.h"

using namespace std;

// global vectors storing different types of geometric objects..
vector<Point2D> point2dArray;
vector<Line2D> line2dArray;
vector<Point3D> point3dArray;
vector<Line3D> line3dArray;
vector<ConnectedLine2D> cLine2dArray;

// flag to chcek if a file has been loaded
bool fileLoaded = false;

// function to read and parse data from a file.
void parseFile(string filename)
{
    filename = trim(filename);  // remove leading trailing whitespaces

    fstream inputFile(filename.c_str(), fstream::in);
    if (!inputFile.is_open())
    {
        throw MyException("Could not open file: " + filename);
    }
    // clear previous data if a file was already loaded.
    if (fileLoaded)
    {
        point2dArray.clear();
        line2dArray.clear();
        point3dArray.clear();
        line3dArray.clear();
        fileLoaded = false;
    }

    string aLine;
    int recordCounter = 0;

    // read file, line by line.
    while (getline(inputFile, aLine))
    {
        if (aLine == "")  // skip empty lines
        {
            continue;
        }

        vector<string> tokens = tokenizeString(aLine, ", ");  // split lines into tokens.

        string className = tokens[0];  // class name expected to be first token.

        // handle each type of object.
        if (className == "Point2D")
        {
            if (tokens.size() != 3)
            {
                throw MyException("Malformed Point2D data: " + aLine);
            }
            processPoint2D(tokens[1], tokens[2]);  // clean up brackets [ ]
            int x = convertFrStringToPrimitiveType<int>(tokens[1]);
            int y = convertFrStringToPrimitiveType<int>(tokens[2]);
            Point2D p1(x, y);
            // check for duplicates
            auto it = find(point2dArray.begin(), point2dArray.end(), p1);
            if (it == point2dArray.end())
            {
                point2dArray.push_back(p1);
                recordCounter++;
            }
        }

        else if (className == "Point3D")
        {
            if (tokens.size() != 4)
            {
                throw MyException("Malformed Point3D data: " + aLine);
            }
            processPoint3D(tokens[1], tokens[2], tokens[3]);  // clean up brackets [ ]

            int x = convertFrStringToPrimitiveType<int>(tokens[1]);
            int y = convertFrStringToPrimitiveType<int>(tokens[2]);
            int z = convertFrStringToPrimitiveType<int>(tokens[3]);
            Point3D p1(x, y, z);
            // check for duplicates
            auto it = find(point3dArray.begin(), point3dArray.end(), p1);
            if (it == point3dArray.end())
            {
                point3dArray.push_back(p1);
                recordCounter++;
            }
        }
        else if (className == "Line2D")
        {
            if (tokens.size() != 5)
            {
                throw MyException("Malformed Line2D data: " + aLine);
            }
            processLine2D(tokens[1], tokens[2], tokens[3], tokens[4]);  // clean up brackets [ ]
            int x1 = convertFrStringToPrimitiveType<int>(tokens[1]);
            int y1 = convertFrStringToPrimitiveType<int>(tokens[2]);
            int x2 = convertFrStringToPrimitiveType<int>(tokens[3]);
            int y2 = convertFrStringToPrimitiveType<int>(tokens[4]);
            Point2D p1(x1, y1);
            Point2D p2(x2, y2);
            Line2D l1(p1, p2);
            // check for duplicates
            auto it = find(line2dArray.begin(), line2dArray.end(), l1);
            if (it == line2dArray.end())
            {
                line2dArray.push_back(l1);
                recordCounter++;
            }
        }
        else if (className == "Line3D")
        {
            if (tokens.size() != 7)
            {
                throw MyException("Malformed Line3D data: " + aLine);
            }
            processLine3D(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5],
                          tokens[6]);  // clean up brackets []
            int x1 = convertFrStringToPrimitiveType<int>(tokens[1]);
            int y1 = convertFrStringToPrimitiveType<int>(tokens[2]);
            int z1 = convertFrStringToPrimitiveType<int>(tokens[3]);
            int x2 = convertFrStringToPrimitiveType<int>(tokens[4]);
            int y2 = convertFrStringToPrimitiveType<int>(tokens[5]);
            int z2 = convertFrStringToPrimitiveType<int>(tokens[6]);
            Point3D p1(x1, y1, z1);
            Point3D p2(x2, y2, z2);
            Line3D l1(p1, p2);
            // check for duplicates
            auto it = find(line3dArray.begin(), line3dArray.end(), l1);
            if (it == line3dArray.end())
            {
                line3dArray.push_back(l1);
                recordCounter++;
            }
        }
        else if (className == "ConnectedLine2D")
        {
            if (tokens.size() != 7)
            {
                throw MyException("Malformed ConnectedLine2D data: " + aLine);
            }
            processConnectedLine2D(tokens[1], tokens[2], tokens[3], tokens[4], tokens[5],
                                   tokens[6]);  // clean up brackets []
            int x1 = convertFrStringToPrimitiveType<int>(tokens[1]);
            int y1 = convertFrStringToPrimitiveType<int>(tokens[2]);
            int connectedX = convertFrStringToPrimitiveType<int>(tokens[3]);
            int connectedY = convertFrStringToPrimitiveType<int>(tokens[4]);
            int x2 = convertFrStringToPrimitiveType<int>(tokens[5]);
            int y2 = convertFrStringToPrimitiveType<int>(tokens[6]);
            Point2D p1(x1, y1);
            Point2D p2(connectedX, connectedY);
            Point2D p3(x2, y2);
            Line2D l1(p1, p2);
            Line2D l2(p2, p3);
            ConnectedLine2D cl1(l1, l2);
            // check for duplicates
            auto it = find(cLine2dArray.begin(), cLine2dArray.end(), cl1);
            if (it == cLine2dArray.end())
            {
                cLine2dArray.push_back(cl1);
                recordCounter++;
            }
        }
        else
        {
            throw MyException("Unknown class name: " + className);
        }
    }

    // number of records read successfully
    cout << recordCounter << " records read in successfully!" << endl << endl;
    cout << "Going back to main menu..." << endl;
    fileLoaded = true;
    inputFile.close();
}

//------------------------------------------------------------------------------------------
// functions to clean up input string by removing brackets.
void processPoint2D(string& xVal, string& yVal)
{
    xVal = xVal.substr(1);                   // remove "["
    yVal = yVal.substr(0, yVal.size() - 1);  // remove "]"
}

void processPoint3D(string& xVal, string& yVal, string& zVal)
{
    xVal = xVal.substr(1);                   // remove "["
    zVal = zVal.substr(0, zVal.size() - 1);  // remove "]"
}

void processLine2D(string& xVal1, string& yVal1, string& xVal2, string& yVal2)
{
    processPoint2D(xVal1, yVal1);
    processPoint2D(xVal2, yVal2);
}

void processLine3D(string& xVal1, string& yVal1, string& zVal1, string& xVal2, string& yVal2,
                   string& zVal2)
{
    processPoint3D(xVal1, yVal1, zVal1);
    processPoint3D(xVal2, yVal2, zVal2);
}

void processConnectedLine2D(string& xVal1, string& yVal1, string& midxVal, string& midyVal,
                            string& xVal2, string& yVal2)
{
    processPoint2D(xVal1, yVal1);
    processPoint2D(midxVal, midyVal);
    processPoint2D(xVal2, yVal2);
}

// Functon to write data to an output file.
void generateOutputFile(string filename)
{
    if (!fileLoaded)
    {
        throw MyException("No data: Please load in a file (menu option 1)");
    }

    fstream outputFile(filename, fstream::out);

    if (!outputFile.is_open())
    {
        throw MyException("Failed to open the output file: " + filename);
    }

    // write the filter settings to the file.
    outputFile << "Filtering criteria: " << filterCriteria << endl;
    outputFile << "Sorting criteria: " << sortingCriteria << endl;
    outputFile << "Sorting order: " << sortingOrder << endl << endl;

    // output data according to the filter type.
    if (filterCriteria == "Point2D")
    {
        sortPoint2D();
        outputFile << getPoint2DString();
    }
    else if (filterCriteria == "Point3D")
    {
        sortPoint3D();
        outputFile << getPoint3DString();
    }
    else if (filterCriteria == "Line2D")
    {
        sortLine2D();
        outputFile << getLine2DString();
    }

    else if (filterCriteria == "Line3D")
    {
        sortLine3D();
        outputFile << getLine3DString();
    }
    else if (filterCriteria == "ConnectedLine2D")
    {
        sortConnectedLine2D();
        outputFile << getConnectedLine2DString();
    }
    else
    {
        throw MyException("Unknown filter criteria: " + filterCriteria);
    }
    cout << endl << "Successfully stored data to '" << filename << "'!" << endl;
    outputFile.close();
}
