#include "Sorting.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "ConnectedLine2D.h"
#include "Line2D.h"
#include "Point2D.h"
#include "Point3D.h"
#include "exceptionClass.h"
#include "menu.h"
#include "processIOFile.h"

using namespace std;

// Main function that sorts and displays data depending on filterCriteria
void sortAndDisplayData()
{
    if (!fileLoaded)  // Checks if file is loaded before continuing
    {
        throw MyException("No data: Please load in a file (menu option 1)");
    }
    // Decide which data to sort based on the filterCriteria
    if (filterCriteria == "Point2D")
    {
        sortPoint2D();
        cout << getPoint2DString();
    }
    else if (filterCriteria == "Point3D")
    {
        sortPoint3D();
        cout << getPoint3DString();
    }
    else if (filterCriteria == "Line2D")
    {
        sortLine2D();
        cout << getLine2DString();
    }

    else if (filterCriteria == "Line3D")
    {
        sortLine3D();
        cout << getLine3DString();
    }
    else if (filterCriteria == "ConnectedLine2D")
    {
        sortConnectedLine2D();
        cout << getConnectedLine2DString();
    }
    else
    {
        throw MyException("Unknown filter criteria: " + filterCriteria);
    }
}
//------------------------------------------------------------------------------------------------------------
// Sorting function for Point2D objects.
void sortPoint2D()
{
    if (sortingCriteria == "x-ordinate" && sortingOrder == "ASC")
    {  // sort by X ascending
        sort(point2dArray.begin(), point2dArray.end(),
             [](Point2D a, Point2D b) { return a.getX() < b.getX(); });
    }
    else if (sortingCriteria == "x-ordinate" && sortingOrder == "DSC")
    {  // sort by X descending
        sort(point2dArray.begin(), point2dArray.end(),
             [](Point2D a, Point2D b) { return a.getX() > b.getX(); });
    }
    else if (sortingCriteria == "y-ordinate" && sortingOrder == "ASC")
    {  // sort by Y ascending
        sort(point2dArray.begin(), point2dArray.end(),
             [](Point2D a, Point2D b) { return a.getY() < b.getY(); });
    }
    else if (sortingCriteria == "y-ordinate" && sortingOrder == "DSC")
    {  // sort by Y descending
        sort(point2dArray.begin(), point2dArray.end(),
             [](Point2D a, Point2D b) { return a.getY() > b.getY(); });
    }
    else if (sortingCriteria == "Dist. Fr Origin" && sortingOrder == "ASC")
    {  // Sort by dist ascending
        sort(point2dArray.begin(), point2dArray.end(),
             [](Point2D a, Point2D b) { return a.getScalarValue() < b.getScalarValue(); });
    }
    else if (sortingCriteria == "Dist. Fr Origin" && sortingOrder == "DSC")
    {  // sort by dist descending
        sort(point2dArray.begin(), point2dArray.end(),
             [](Point2D a, Point2D b) { return a.getScalarValue() > b.getScalarValue(); });
    }
    else
    {
        throw MyException("Sorting Point2D error");
    }
}

// Sorting function for Point3D objects.
// Same as Point2D but has z-ordinate
void sortPoint3D()
{
    if (sortingCriteria == "x-ordinate" && sortingOrder == "ASC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getX() < b.getX(); });
    }
    else if (sortingCriteria == "x-ordinate" && sortingOrder == "DSC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getX() > b.getX(); });
    }
    else if (sortingCriteria == "y-ordinate" && sortingOrder == "ASC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getY() < b.getY(); });
    }
    else if (sortingCriteria == "y-ordinate" && sortingOrder == "DSC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getY() > b.getY(); });
    }
    else if (sortingCriteria == "z-ordinate" && sortingOrder == "ASC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getZ() < b.getZ(); });
    }
    else if (sortingCriteria == "z-ordinate" && sortingOrder == "DSC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getZ() > b.getZ(); });
    }
    else if (sortingCriteria == "Dist. Fr Origin" && sortingOrder == "ASC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getScalarValue() < b.getScalarValue(); });
    }
    else if (sortingCriteria == "Dist. Fr Origin" && sortingOrder == "DSC")
    {
        sort(point3dArray.begin(), point3dArray.end(),
             [](Point3D a, Point3D b) { return a.getScalarValue() > b.getScalarValue(); });
    }
    else
    {
        throw MyException("Sorting Point3D error");
    }
}

// Sorting for Line2D objects
//  Can sort by pt1, pt2 or length
void sortLine2D()
{
    if (sortingCriteria == "Pt. 1" && sortingOrder == "ASC")
    {  // Compare first by X of Pt1, then by Y if equal.
        sort(line2dArray.begin(), line2dArray.end(),
             [](Line2D a, Line2D b)
             {
                 return (a.getPt1().getX() < b.getPt1().getX()) ||
                        (a.getPt1().getX() == b.getPt1().getX() &&
                         a.getPt1().getY() < b.getPt1().getY());
             });
        //     return (y < rhs.y) || (y == rhs.y && x < rhs.x);
    }
    else if (sortingCriteria == "Pt. 1" && sortingOrder == "DSC")
    {
        sort(line2dArray.begin(), line2dArray.end(),
             [](Line2D a, Line2D b)
             {
                 return (a.getPt1().getX() > b.getPt1().getX()) ||
                        (a.getPt1().getX() == b.getPt1().getX() &&
                         a.getPt1().getY() > b.getPt1().getY());
             });
    }
    else if (sortingCriteria == "Pt. 2" && sortingOrder == "ASC")
    {
        sort(line2dArray.begin(), line2dArray.end(),
             [](Line2D a, Line2D b)
             {
                 return (a.getPt2().getX() < b.getPt2().getX()) ||
                        (a.getPt2().getX() == b.getPt2().getX() &&
                         a.getPt2().getY() < b.getPt2().getY());
             });
    }
    else if (sortingCriteria == "Pt. 2" && sortingOrder == "DSC")
    {
        sort(line2dArray.begin(), line2dArray.end(),
             [](Line2D a, Line2D b)
             {
                 return (a.getPt2().getX() > b.getPt2().getX()) ||
                        (a.getPt2().getX() == b.getPt2().getX() &&
                         a.getPt2().getY() > b.getPt2().getY());
             });
    }
    else if (sortingCriteria == "Length" && sortingOrder == "ASC")
    {
        sort(line2dArray.begin(), line2dArray.end(),
             [](Line2D a, Line2D b) { return a.getScalarValue() < b.getScalarValue(); });
    }
    else if (sortingCriteria == "Length" && sortingOrder == "DSC")
    {
        sort(line2dArray.begin(), line2dArray.end(),
             [](Line2D a, Line2D b) { return a.getScalarValue() > b.getScalarValue(); });
    }
    else
    {
        throw MyException("Sorting Line2D error");
    }
}

// Sorting Line3D objects..
// Same as Line2D but with 3D points.
void sortLine3D()
{
    if (sortingCriteria == "Pt. 1" && sortingOrder == "ASC")
    {
        sort(line3dArray.begin(), line3dArray.end(),
             [](Line3D a, Line3D b)
             {
                 return (a.getPt1().getX() < b.getPt1().getX()) ||
                        (a.getPt1().getX() == b.getPt1().getX() &&
                         a.getPt1().getY() < b.getPt1().getY());
             });
    }
    else if (sortingCriteria == "Pt. 1" && sortingOrder == "DSC")
    {
        sort(line3dArray.begin(), line3dArray.end(),
             [](Line3D a, Line3D b)
             {
                 return (a.getPt1().getX() > b.getPt1().getX()) ||
                        (a.getPt1().getX() == b.getPt1().getX() &&
                         a.getPt1().getY() > b.getPt1().getY());
             });
    }
    else if (sortingCriteria == "Pt. 2" && sortingOrder == "ASC")
    {
        sort(line3dArray.begin(), line3dArray.end(),
             [](Line3D a, Line3D b)
             {
                 return (a.getPt2().getX() < b.getPt2().getX()) ||
                        (a.getPt2().getX() == b.getPt2().getX() &&
                         a.getPt2().getY() < b.getPt2().getY());
             });
    }
    else if (sortingCriteria == "Pt. 2" && sortingOrder == "DSC")
    {
        sort(line3dArray.begin(), line3dArray.end(),
             [](Line3D a, Line3D b)
             {
                 return (a.getPt2().getX() > b.getPt2().getX()) ||
                        (a.getPt2().getX() == b.getPt2().getX() &&
                         a.getPt2().getY() > b.getPt2().getY());
             });
    }
    else if (sortingCriteria == "Length" && sortingOrder == "ASC")
    {
        sort(line3dArray.begin(), line3dArray.end(),
             [](Line3D a, Line3D b) { return a.getScalarValue() < b.getScalarValue(); });
    }
    else if (sortingCriteria == "Length" && sortingOrder == "DSC")
    {
        sort(line3dArray.begin(), line3dArray.end(),
             [](Line3D a, Line3D b) { return a.getScalarValue() > b.getScalarValue(); });
    }
    else
    {
        throw MyException("Sorting Line3D error");
    }
}

// Sorting ConnectedLine2D objects
// each ConnectedLine2D consists of two connected Line2D segments.
// Can be sorted by pt1, pt2, pt3 or total length
void sortConnectedLine2D()
{
    if (sortingCriteria == "Pt. 1" && sortingOrder == "ASC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(),
             [](ConnectedLine2D a, ConnectedLine2D b)
             {
                 return (a.getLine1().getPt1().getX() < b.getLine1().getPt1().getX()) ||
                        (a.getLine1().getPt1().getX() == b.getLine1().getPt1().getX() &&
                         a.getLine1().getPt1().getY() < b.getLine1().getPt1().getY());
             });
    }
    else if (sortingCriteria == "Pt. 1" && sortingOrder == "DSC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(),
             [](ConnectedLine2D a, ConnectedLine2D b)
             {
                 return (a.getLine1().getPt1().getX() > b.getLine1().getPt1().getX()) ||
                        (a.getLine1().getPt1().getX() == b.getLine1().getPt1().getX() &&
                         a.getLine1().getPt1().getY() > b.getLine1().getPt1().getY());
             });
    }
    else if (sortingCriteria == "Pt. 2" && sortingOrder == "ASC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(),
             [](ConnectedLine2D a, ConnectedLine2D b)
             {
                 return (a.getLine1().getPt2().getX() < b.getLine1().getPt2().getX()) ||
                        (a.getLine1().getPt2().getX() == b.getLine1().getPt2().getX() &&
                         a.getLine1().getPt2().getY() < b.getLine1().getPt2().getY());
             });
    }
    else if (sortingCriteria == "Pt. 2" && sortingOrder == "DSC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(),
             [](ConnectedLine2D a, ConnectedLine2D b)
             {
                 return (a.getLine1().getPt2().getX() > b.getLine1().getPt2().getX()) ||
                        (a.getLine1().getPt2().getX() == b.getLine1().getPt2().getX() &&
                         a.getLine1().getPt2().getY() > b.getLine1().getPt2().getY());
             });
    }
    else if (sortingCriteria == "Pt. 3" && sortingOrder == "ASC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(),
             [](ConnectedLine2D a, ConnectedLine2D b)
             {
                 return (a.getLine2().getPt2().getX() < b.getLine2().getPt2().getX()) ||
                        (a.getLine2().getPt2().getX() == b.getLine2().getPt2().getX() &&
                         a.getLine2().getPt2().getY() < b.getLine2().getPt2().getY());
             });
    }
    else if (sortingCriteria == "Pt. 3" && sortingOrder == "DSC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(),
             [](ConnectedLine2D a, ConnectedLine2D b)
             {
                 return (a.getLine2().getPt2().getX() > b.getLine2().getPt2().getX()) ||
                        (a.getLine2().getPt2().getX() == b.getLine2().getPt2().getX() &&
                         a.getLine2().getPt2().getY() > b.getLine2().getPt2().getY());
             });
    }
    else if (sortingCriteria == "Total Length" && sortingOrder == "ASC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(), [](ConnectedLine2D a, ConnectedLine2D b)
             { return a.getTotalLength() < b.getTotalLength(); });
    }
    else if (sortingCriteria == "Total Length" && sortingOrder == "DSC")
    {
        sort(cLine2dArray.begin(), cLine2dArray.end(), [](ConnectedLine2D a, ConnectedLine2D b)
             { return a.getTotalLength() > b.getTotalLength(); });
    }
    else
    {
        throw MyException("Sorting ConnectedLine2D error");
    }
}
//-------------------------------------------------------------------------------------------------------------------------
// Formatting functions
// returns the string representation of sorted data
// These functions add headers and column alignment.
//
string getPoint2DString()
{
    ostringstream oss;
    oss << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(19)
        << "Dist. Fr Origin" << endl;
    oss << "----------------------------------" << endl;
    for (Point2D x : point2dArray)
    {
        oss << x << endl;
    }
    oss << endl;
    return oss.str();
}

string getPoint3DString()
{
    ostringstream oss;
    oss << right << setw(5) << "X" << right << setw(6) << "Y" << right << setw(6) << "Z" << right
        << setw(19) << "Dist. Fr Origin" << endl;
    oss << "---------------------------------------" << endl;

    for (Point3D x : point3dArray)
    {
        oss << x << endl;
    }
    oss << endl;
    return oss.str();
}

string getLine2DString()
{
    ostringstream oss;
    oss << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y" << right << setw(9) << "P2-X"
        << right << setw(6) << "P2-Y" << right << setw(10) << "Length" << endl;
    oss << "------------------------------------------" << endl;
    for (Line2D x : line2dArray)
    {
        oss << x << endl;
    }
    oss << endl;
    return oss.str();
}

string getLine3DString()
{
    ostringstream oss;
    oss << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y" << right << setw(6) << "P1-Z"
        << right << setw(9) << "P2-X" << right << setw(6) << "P2-Y" << right << setw(6) << "P2-Z"
        << right << setw(10) << "Length" << endl;
    oss << "-----------------------------------------------------" << endl;
    for (Line3D x : line3dArray)
    {
        oss << x << endl;
    }
    oss << endl;
    return oss.str();
}

string getConnectedLine2DString()
{
    ostringstream oss;
    oss << right << setw(5) << "P1-X" << right << setw(6) << "P1-Y" << right << setw(9) << "P2-X"
        << right << setw(6) << "P2-Y" << right << setw(9) << "P3-X" << right << setw(6) << "P3-Y"
        << right << setw(16) << "Total Length" << endl;
    oss << "-----------------------------------------------------------" << endl;
    for (ConnectedLine2D x : cLine2dArray)
    {
        oss << x << endl;
    }
    oss << endl;
    return oss.str();
}
