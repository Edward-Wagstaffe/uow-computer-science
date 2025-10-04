
#include "Ellipse.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "ShapeTwoD.h"

//-------------------------------------------------------
// Constructors
Ellipse::Ellipse() {};

Ellipse::Ellipse(string nm, bool cWS) : ShapeTwoD(nm, cWS) {};

//--------------------------------------------------------
// Operator overloading

// Outputs the string representation for a square using << syntax
// #elegance
ostream& operator<<(ostream& sOut, Ellipse& obj)
{
    sOut << obj.toString();
    return sOut;
}

// Allows input of a Square object using >> syntax
// #elegance
istream& operator>>(istream& sIn, Ellipse& obj)
{
    cout << "Please enter x-ordinate of center: ";
    Point point;
    sIn >> point.x;
    if (sIn.fail() || point.x < 0)
    {
        sIn.clear();           // clear the error flag
        sIn.ignore(80, '\n');  // discard the bad input
        throw invalid_argument("Invalid x-ordinate: must be a positive integer.");
    }

    cout << "Please enter y-ordinate of center: ";
    sIn >> point.y;
    if (sIn.fail() || point.y < 0)
    {
        sIn.clear();           // clear the error flag
        sIn.ignore(80, '\n');  // discard the bad input
        throw invalid_argument("Invalid y-ordinate: must be a positive integer.");
    }

    obj.center = point;

    cout << "Please enter x-radius (units): ";
    sIn >> obj.xRadius;
    if (sIn.fail() || obj.xRadius < 0)
    {
        sIn.clear();           // clear the error flag
        sIn.ignore(80, '\n');  // discard the bad input
        throw invalid_argument("Invalid x-radius: must be a positive integer.");
    }

    cout << "Please enter y-radius (units): ";
    sIn >> obj.yRadius;
    if (sIn.fail() || obj.yRadius < 0)
    {
        sIn.clear();           // clear the error flag
        sIn.ignore(80, '\n');  // discard the bad input
        throw invalid_argument("Invalid y-radius: must be a positive integer.");
    }

    return sIn;
}

//--------------------------------------------------------------------
// virtual member functions to be overriden.
// returns the string representation for a Ellipse, includes area, center point, x raidus, y radius,
// points on perimeter, points within shape
string Ellipse::toString()
{
    ostringstream oss;
    oss << ShapeTwoD::toString();
    if (area)
    {
        oss << "Area: " << fixed << setprecision(2) << area << " units square" << endl;
    }
    else
    {
        oss << "Area: Not calculated! " << endl;
    }
    oss << "Center point: " << center << endl;
    oss << "x Radius: " << xRadius << endl;
    oss << "y Radius: " << yRadius << endl;
    oss << endl;

    // display points on north south east west
    oss << "Points on perimeter: ";
    vector<Point> pointsOnShape = getPointsOnShape();
    if (pointsOnShape.empty())
    {
        oss << "none!" << endl;
    }
    else
    {
        for (int i = 0; i < pointsOnShape.size(); i++)
        {
            if (i != pointsOnShape.size() - 1)
            {
                oss << pointsOnShape[i] << ", ";
            }
            else
            {
                oss << pointsOnShape[i] << endl;
            }
        }
    }
    oss << endl;

    // display points inside ellipse, excluding center
    oss << "Points within shape: ";
    vector<Point> pointsInShape = getPointsInShape();
    if (pointsInShape.empty())
    {
        oss << "none!" << endl;
    }
    else
    {
        for (int i = 0; i < pointsInShape.size(); i++)
        {
            if (i != pointsInShape.size() - 1)
            {
                oss << pointsInShape[i] << ", ";
            }
            else
            {
                oss << pointsInShape[i] << endl;
            }
        }
    }
    return oss.str();
}

// computes the area of an ellipse (PI * xradius * yradius)
double Ellipse::computeArea() const
{
    const double PI = 3.141592653589793;
    return PI * xRadius * yRadius;
}

// returns true if (x,y) lies inside the ellipse
bool Ellipse::isPointInShape(int x, int y) const
{
    double dx = x - center.x;
    double dy = y - center.y;
    double result = (dx * dx) / (xRadius * xRadius) + (dy * dy) / (yRadius * yRadius);
    return result < 1.0;
}

// returns true if (x,y) lies north south east west of center
bool Ellipse::isPointOnShape(int x, int y) const
{
    return (x == center.x &&
            (y == center.y + yRadius || y == center.y - yRadius)) ||  // North or South
           (y == center.y && (x == center.x + xRadius || x == center.x - xRadius));  // East or West
}

// returns all points enclosed by the bounding box
vector<Point> Ellipse::getEnclosingPoints()
{
    int minX = center.x - xRadius;
    int minY = center.y - yRadius;
    int maxX = center.x + xRadius;
    int maxY = center.y + yRadius;

    vector<Point> enclosingPoints;
    for (int x = minX; x <= maxX; x++)
    {
        for (int y = minY; y <= maxY; y++)
        {
            enclosingPoints.emplace_back(x, y);
        }
    }
    return enclosingPoints;
}

// returns the points that are on the north, south ,east, west of center.
vector<Point> Ellipse::getPointsOnShape()
{
    vector<Point> enclosedPoints = getEnclosingPoints();

    vector<Point> pointsOnShape;
    for (int i = 0; i < enclosedPoints.size(); i++)
    {
        int x = enclosedPoints[i].x;
        int y = enclosedPoints[i].y;
        if (isPointOnShape(x, y))
        {
            pointsOnShape.emplace_back(x, y);
        }
    }
    return pointsOnShape;
}

// returns the points that are inside the shape, excluding center
vector<Point> Ellipse::getPointsInShape()
{
    vector<Point> enclosedPoints = getEnclosingPoints();
    vector<Point> pointsInShape;
    for (int i = 0; i < enclosedPoints.size(); i++)
    {
        int x = enclosedPoints[i].x;
        int y = enclosedPoints[i].y;
        if (isPointInShape(x, y) && !(x == center.x && y == center.y))
        {
            pointsInShape.emplace_back(x, y);
        }
    }
    return pointsInShape;
}
