
#include "Cross.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "ShapeTwoD.h"

//-------------------------------------------------------
// Constructors
Cross::Cross() {};

Cross::Cross(string nm, bool cWS) : ShapeTwoD(nm, cWS) {};

//--------------------------------------------------------
// Operator overloading

// Outputs the string representation for a square using << syntax
// #elegance
ostream& operator<<(ostream& sOut, Cross& obj)
{
    sOut << obj.toString();
    return sOut;
}

// Allows input of a Square object using >> syntax
// #elegance
istream& operator>>(istream& sIn, Cross& obj)
{
    for (int i = 0; i < 12; i++)
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
    if (!(obj.isCross()))
    {
        obj.nextID--;
        throw(obj);
    }
    return sIn;
}

//--------------------------------------------------------------------
// virtual member functions to be overriden.
// returns the string representation for a Cross, includes area, 12 vertices, points on perimeter,
// points within shape

string Cross::toString()
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

// computes the area of a cross by taking off the area of the 4 corner rectangles from the large
// enclosing rectangle
double Cross::computeArea() const
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    Point btmArmLeft = temp[0];
    Point btmArmRight = temp[1];
    Point leftArmBtm = temp[2];
    Point innerBtmLeft = temp[3];
    Point innerBtmRight = temp[4];
    Point rightArmBtm = temp[5];
    Point leftArmTop = temp[6];
    Point innerTopLeft = temp[7];
    Point innerTopRight = temp[8];
    Point rightArmTop = temp[9];
    Point topArmLeft = temp[10];
    Point topArmRight = temp[11];

    // get the area of the 4 corner rectangles
    double topLeftArea = (topArmLeft.y - innerTopLeft.y) * (innerTopLeft.x - leftArmTop.x);
    double topRightArea = (topArmRight.y - innerTopRight.y) * (rightArmTop.x - innerTopRight.x);
    double btmLeftArea = (innerBtmLeft.y - btmArmLeft.y) * (innerBtmLeft.x - leftArmBtm.x);
    double btmRightArea = (rightArmBtm.x - innerBtmRight.x) * (innerBtmRight.y - btmArmRight.y);
    // get the area of the big rectangle enclosing the cross
    double bigRectangle = (topArmLeft.y - btmArmLeft.y) * (rightArmTop.x - leftArmTop.x);

    return bigRectangle - topLeftArea - topRightArea - btmLeftArea - btmRightArea;
}

// returns true if (x,y) lies inside the Cross
bool Cross::isPointInShape(int x, int y) const
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    Point btmArmLeft = temp[0];
    Point btmArmRight = temp[1];
    Point leftArmBtm = temp[2];
    Point innerBtmLeft = temp[3];
    Point innerBtmRight = temp[4];
    Point rightArmBtm = temp[5];
    Point leftArmTop = temp[6];
    Point innerTopLeft = temp[7];
    Point innerTopRight = temp[8];
    Point rightArmTop = temp[9];
    Point topArmLeft = temp[10];
    Point topArmRight = temp[11];

    // Check if point is within the large rectangle
    int minX = leftArmBtm.x;
    int maxX = rightArmTop.x;
    int minY = btmArmLeft.y;
    int maxY = topArmLeft.y;

    if (x <= minX || x >= maxX || y <= minY || y >= maxY)
    {
        return false;
    }

    // Check if point is in any of the subtracted corner rectangles
    // Top-left corner rectangle
    if (x >= leftArmTop.x && x <= innerTopLeft.x && y >= innerTopLeft.y && y <= topArmLeft.y)
    {
        return false;
    }
    // Top-right corner rectangle
    if (x >= innerTopRight.x && x <= rightArmTop.x && y >= innerTopRight.y && y <= topArmRight.y)
    {
        return false;
    }
    // Bottom-left corner rectangle
    if (x >= leftArmBtm.x && x <= innerBtmLeft.x && y >= btmArmLeft.y && y <= innerBtmLeft.y)
    {
        return false;
    }
    // Bottom-right corner rectangle
    if (x >= innerBtmRight.x && x <= rightArmBtm.x && y >= btmArmRight.y && y <= innerBtmRight.y)
    {
        return false;
    }

    return true;
}

// returns true if (x,y) is on the cross perimeter, excluding the vertices
bool Cross::isPointOnShape(int x, int y) const
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());

    // Assign vertices based on sorted order
    Point btmArmLeft = temp[0];
    Point btmArmRight = temp[1];
    Point leftArmBtm = temp[2];
    Point innerBtmLeft = temp[3];
    Point innerBtmRight = temp[4];
    Point rightArmBtm = temp[5];
    Point leftArmTop = temp[6];
    Point innerTopLeft = temp[7];
    Point innerTopRight = temp[8];
    Point rightArmTop = temp[9];
    Point topArmLeft = temp[10];
    Point topArmRight = temp[11];

    // Check if the point is one of the 12 vertices
    if ((x == btmArmLeft.x && y == btmArmLeft.y) || (x == btmArmRight.x && y == btmArmRight.y) ||
        (x == leftArmBtm.x && y == leftArmBtm.y) || (x == innerBtmLeft.x && y == innerBtmLeft.y) ||
        (x == innerBtmRight.x && y == innerBtmRight.y) ||
        (x == rightArmBtm.x && y == rightArmBtm.y) || (x == leftArmTop.x && y == leftArmTop.y) ||
        (x == innerTopLeft.x && y == innerTopLeft.y) ||
        (x == innerTopRight.x && y == innerTopRight.y) ||
        (x == rightArmTop.x && y == rightArmTop.y) || (x == topArmLeft.x && y == topArmLeft.y) ||
        (x == topArmRight.x && y == topArmRight.y))
    {
        return false;
    }

    // check if the point is between each vertice pair that forms an edge, non inclusive of the
    // vertices.
    bool onEdge1 = (y == leftArmTop.y && x < innerTopLeft.x && x > leftArmTop.x);
    bool onEdge2 = (x == innerTopLeft.x && y < topArmLeft.y && y > innerTopLeft.y);
    bool onEdge3 = (y == topArmLeft.y && x < topArmRight.x && x > topArmLeft.x);
    bool onEdge4 = (x == topArmRight.x && y < topArmRight.y && y > innerTopRight.y);
    bool onEdge5 = (y == innerTopRight.y && x < rightArmTop.x && x > innerTopRight.x);
    bool onEdge6 = (x == rightArmTop.x && y < rightArmTop.y && y > rightArmBtm.y);
    bool onEdge7 = (y == rightArmBtm.y && x < rightArmBtm.x && x > innerBtmRight.x);
    bool onEdge8 = (x == innerBtmRight.x && y < innerBtmRight.y && y > btmArmRight.y);
    bool onEdge9 = (y == btmArmRight.y && x < btmArmRight.x && x > btmArmLeft.x);
    bool onEdge10 = (x == btmArmLeft.x && y < innerBtmLeft.y && y > btmArmLeft.y);
    bool onEdge11 = (y == innerBtmLeft.y && x < innerBtmLeft.x && x > leftArmBtm.x);
    bool onEdge12 = (x == leftArmBtm.x && y < leftArmTop.y && y > leftArmBtm.y);

    return (onEdge1 || onEdge2 || onEdge3 || onEdge4 || onEdge5 || onEdge6 || onEdge7 || onEdge8 ||
            onEdge9 || onEdge10 || onEdge11 || onEdge12);
}

// returns all the points that enclose the cross (bounding box)
vector<Point> Cross::getEnclosingPoints()
{
    // Sort vertices to identify key points consistently
    vector<Point> temp = vertices;
    sort(temp.begin(), temp.end());  // Point operator< is overloaded so makes this possible

    Point btmLeft(temp[2].x, temp[0].y);
    Point topRight(temp[5].x, temp[10].y);

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
vector<Point> Cross::getPointsOnShape()
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
vector<Point> Cross::getPointsInShape()
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
// validates that the 12 input points form a symmetrical cross/lopsided cross
bool Cross::isCross()
{
    // This logic is quite difficult, I shall code it later if I have time.
    // This error checking is not part of the min requirements, but would be nice to have.
    return true;
}
