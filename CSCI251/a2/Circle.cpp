
#include "Circle.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "ShapeTwoD.h"

//-------------------------------------------------------
// Constructors
Circle::Circle() {};

Circle::Circle(string nm, bool cWS) : ShapeTwoD(nm, cWS) {};

//--------------------------------------------------------
// Operator overloading

// Outputs the string representation for a Circle using << syntax
// #elegance
ostream& operator<<(ostream& sOut, Circle& obj)
{
    sOut << obj.toString();
    return sOut;
}

// Allows input of a Circle object using >> syntax
// #elegance
istream& operator>>(istream& sIn, Circle& obj)
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

    cout << "Please enter radius (units): ";
    sIn >> obj.radius;
    if (sIn.fail() || obj.radius < 0)
    {
        sIn.clear();           // clear the error flag
        sIn.ignore(80, '\n');  // discard the bad input
        throw invalid_argument("Invalid radius: must be a positive integer.");
    }

    return sIn;
}
//--------------------------------------------------------------------
// virtual member functions to be overriden.
// returns the string representation for a Square, includes area, center point,radius, points on
// perimeter, points within shape
string Circle::toString()
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
    oss << "Radius: " << radius << endl;
    oss << endl;
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
// computes the area of a circle (PI * r^2)
double Circle::computeArea() const
{
    const double PI = 3.141592653589793;
    return PI * radius * radius;
}

// returns true if (x,y) lies inside the circle.
bool Circle::isPointInShape(int x, int y) const
{
    int dx = x - center.x;
    int dy = y - center.y;
    return dx * dx + dy * dy < radius * radius;
}

// returns true if (x,y) lies north south east west of center.
bool Circle::isPointOnShape(int x, int y) const
{
    return (x == center.x &&
            (y == center.y + radius || y == center.y - radius)) ||                 // North or South
           (y == center.y && (x == center.x + radius || x == center.x - radius));  // East or West
}

// returns all points enclosed by the bounding box
vector<Point> Circle::getEnclosingPoints()
{
    int minX = center.x - radius;
    int minY = center.y - radius;
    int maxX = center.x + radius;
    int maxY = center.y + radius;

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
// returns the points that are on the north, south, east, west of center.
vector<Point> Circle::getPointsOnShape()
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

// returns the points that are inside the shape, excluding the center.
vector<Point> Circle::getPointsInShape()
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
