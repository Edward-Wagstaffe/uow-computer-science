#include "Line2D.h"

#include <cmath>
#include <iomanip>
#include <sstream>

#include "Point2D.h"

using namespace std;

//-----------------------------------------------------------------
// Constructors
//
Line2D::Line2D() {};

Line2D::Line2D(Point2D pt1, Point2D pt2) : pt1(pt1), pt2(pt2)
{
    setLength();
}

//------------------------------------------------------------------
// Operator Overloading, friend and member functions
ostream& operator<<(ostream& out, Line2D& obj)
{
    out << obj.toString();
    return out;
}

bool Line2D::operator==(const Line2D& other) const
{
    return (pt1 == other.pt1 && pt2 == other.pt2);
}

//-------------------------------------------------------------------
// Member function
string Line2D::toString()
{
    ostringstream oss;
    oss << "[" << right << setw(4) << pt1.getX() << ", " << right << setw(4) << pt1.getY()
        << "]   ";
    oss << "[" << right << setw(4) << pt2.getX() << ", " << right << setw(4) << pt2.getY()
        << "]   ";
    oss << fixed << setprecision(3) << length;
    return oss.str();
}

//------------------------------------------------------------------
// Getters

double Line2D::getScalarValue()
{
    return length;
}

Point2D Line2D::getPt1()
{
    return pt1;
}
Point2D Line2D::getPt2()
{
    return pt2;
}

//--------------------------------------------------------------------
// Setters

void Line2D::setPt1(Point2D pt1)
{
    this->pt1 = pt1;
}

void Line2D::setPt2(Point2D pt2)
{
    this->pt2 = pt2;
}

void Line2D::setLength()
{
    length = sqrt((pow((pt1.getX() - pt2.getX()), 2)) + pow((pt1.getY() - pt2.getY()), 2));
}
