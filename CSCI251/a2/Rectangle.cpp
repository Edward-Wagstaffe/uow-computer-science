
#include "Rectangle.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "ShapeTwoD.h"
using namespace std;

//-------------------------------------------------------
// Constructors
Rectangle::Rectangle() {};

Rectangle::Rectangle(string nm, bool cWS) : ShapeTwoD(nm, cWS) {};

//--------------------------------------------------------
// Operator overloading

// Outputs the string representation for a Rectangle using << syntax
// #elegance
ostream& operator<<(ostream& sOut, Rectangle& obj)
{
    sOut << obj.toString();
    return sOut;
}
// Allows input of a Rectangle object using >> syntax
// #elegance
istream& operator>>(istream& sIn, Rectangle& obj)
{
    for (int i = 0; i < 4; i++)
    {
        cout << "Please enter x-ordinate of pt" << i + 1 << ": ";
        Point vertex;
        sIn >> vertex.x;
        if (sIn.fail() || vertex.x < 0)
        {
            sIn.clear();           // clear the error flag
            sIn.ignore(80, '\n');  // discard the bad input
            throw invalid_argument("Invalid x-ordinate: must be a positive integer.");
        }

        cout << "Please enter y-ordinate of pt" << i + 1 << ": ";
        sIn >> vertex.y;
        if (sIn.fail() || vertex.y < 0)
        {
            sIn.clear();           // clear the error flag
            sIn.ignore(80, '\n');  // discard the bad input
            throw invalid_argument("Invalid y-ordinate: must be a positive integer.");
        }

        obj.vertices.push_back(vertex);
    }
    if (!(obj.isRectangle()))
    {
        obj.nextID--;
        throw(obj);
    }
    return sIn;
}
//--------------------------------------------------------------------
// virtual member functions to be overriden.
// returns the string representation for a Rectangle includes area, 4 vertices, points on perimeter,
// points within shape
string Rectangle::toString()
{
    ostringstream oss;
    oss << ShapeTwoD::toString();
    if (area)
    {
        oss << "Area: " << area << " units square" << endl;
    }
    else
    {
        oss << "Area: Not calculated! " << endl;
    }
    oss << "Vertices:" << endl;
    for (int i = 0; i < vertices.size(); i++)
    {
        oss << "Point[" << i << "]: " << vertices[i] << endl;
    }
    oss << endl;

    // display points on perimeter, exluding vertices
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

    // display points inside Rectangle
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

// computes the area of a Rectangle (width * height)
double Rectangle::computeArea() const
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    double width = temp[1].x - temp[0].x;
    double height = temp[2].y - temp[0].y;  // top left Y value - bottom left Y value

    return width * height;
}

// returns true if (x,y) lies inside the Rectangle
bool Rectangle::isPointInShape(int x, int y) const
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    Point btmLeft = temp[0];
    Point btmRight = temp[1];
    Point topLeft = temp[2];
    Point topRight = temp[3];

    int minX = btmLeft.x;
    int maxX = topRight.x;
    int minY = btmLeft.y;
    int maxY = topRight.y;

    // Check if point is strictly inside
    return (x > minX && x < maxX && y > minY && y < maxY);
}

// returns true if (x,y) lies on the edge excluding vertices
bool Rectangle::isPointOnShape(int x, int y) const
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    Point btmLeft = temp[0];
    Point btmRight = temp[1];
    Point topLeft = temp[2];
    Point topRight = temp[3];

    // if the point is one of the vertices
    if ((x == btmLeft.x && y == btmLeft.y) || (x == btmRight.x && y == btmRight.y) ||
        (x == topLeft.x && y == topLeft.y) || (x == topRight.x && y == topRight.y))
    {
        return false;
    }

    // check if point is on the perimeter
    bool onLeftOrRightEdge =
        (x == btmLeft.x || x == btmRight.x) && (y >= btmLeft.y && y <= topLeft.y);

    bool onTopOrBottomEdge =
        (y == btmLeft.y || y == topLeft.y) && (x >= btmLeft.x && x <= btmRight.x);

    return (onTopOrBottomEdge || onLeftOrRightEdge);
}
// returns all points enclosed by the rectangle
vector<Point> Rectangle::getEnclosingPoints()
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());  // Point operator< is overloaded so makes this possible

    Point btmLeft = temp[0];
    Point topRight = temp[3];

    int minX = btmLeft.x;
    int minY = btmLeft.y;
    int maxX = topRight.x;
    int maxY = topRight.y;

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

// returns the points that are on the perimeter
vector<Point> Rectangle::getPointsOnShape()
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

// returns the points that are inside the shape
vector<Point> Rectangle::getPointsInShape()
{
    vector<Point> enclosedPoints = getEnclosingPoints();
    vector<Point> pointsInShape;
    for (int i = 0; i < enclosedPoints.size(); i++)
    {
        int x = enclosedPoints[i].x;
        int y = enclosedPoints[i].y;
        if (isPointInShape(x, y))
        {
            pointsInShape.emplace_back(x, y);
        }
    }
    return pointsInShape;
}

//----------------------------------------------------------------
// Shape validation
// validates that the 4 input points form a square
bool Rectangle::isRectangle()
{
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    Point btmLeft = temp[0];
    Point btmRight = temp[1];
    Point topLeft = temp[2];
    Point topRight = temp[3];

    bool verticals = (btmLeft.x == topLeft.x) && (btmRight.x == topRight.x);
    bool horizontals = (btmLeft.y == btmRight.y) && (topLeft.y == topRight.y);

    // Check opposite sides are equal

    int height1 = topLeft.y - btmLeft.y;    // vertical height on left side
    int height2 = topRight.y - btmRight.y;  // vertical height on right side

    int width1 = btmRight.x - btmLeft.x;  // horizontal width on bottom side
    int width2 = topRight.x - topLeft.x;  // horizontal width on top side

    return verticals && horizontals && (height1 == height2) && (width1 == width2);
}
