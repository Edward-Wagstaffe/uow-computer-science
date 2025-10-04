#include "Point.h"

#include <sstream>

//-------------------------------------------------------
// Constructors
Point::Point() {};
Point::Point(int xVal, int yVal)
{
    x = xVal;
    y = yVal;
}

//--------------------------------------------------------
// Operator overloading
// outputs the string representation for Point using << syntax

ostream& operator<<(ostream& sOut, Point& obj)
{
    sOut << obj.toString();
    return sOut;
}

// allows points to be sorted using sort()
// Sort primarily by y, then by x,
// points are sorted bottom left to top right of any given shape
bool Point::operator<(const Point& rhs)
{
    return (y < rhs.y) || (y == rhs.y && x < rhs.x);
}

// returns the string representation of a point
string Point::toString()
{
    ostringstream oss;
    oss << "(" << x << ", " << y << ")";
    return oss.str();
}
