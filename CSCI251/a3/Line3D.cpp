#include "Line3D.h"

#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

//-----------------------------------------------------------------
// Constructors
//
Line3D::Line3D() {}
Line3D::Line3D(Point3D pt1, Point3D pt2) : pt1(pt1), pt2(pt2)
{
    setLength();
}
//------------------------------------------------------------------
// Operator Overloading, friend and member functions
ostream& operator<<(ostream& out, Line3D& obj)
{
    out << obj.toString();
    return out;
}

bool Line3D::operator==(const Line3D& other) const
{
    return (pt1 == other.pt1 && pt2 == other.pt2);
}
//-------------------------------------------------------------------
// Member function
string Line3D::toString()
{
    ostringstream oss;
    oss << "[" << right << setw(4) << pt1.getX() << ", " << right << setw(4) << pt1.getY() << ", "
        << right << setw(4) << pt1.getZ() << "]   ";
    oss << "[" << right << setw(4) << pt2.getX() << ", " << right << setw(4) << pt2.getY() << ", "
        << right << setw(4) << pt1.getZ() << "]   ";
    oss << fixed << setprecision(3) << length;
    return oss.str();
}

//------------------------------------------------------------------
// Getters
Point3D Line3D::getPt1()
{
    return pt1;
}

Point3D Line3D::getPt2()
{
    return pt2;
}

//--------------------------------------------------------------------
// Setters

void Line3D::setPt1(Point3D pt1)
{
    this->pt1 = pt1;
}

void Line3D::setPt2(Point3D pt2)
{
    this->pt2 = pt2;
}

void Line3D::setLength()
{
    length = sqrt((pow((pt1.getX() - pt2.getX()), 2)) + pow((pt1.getY() - pt2.getY()), 2) +
                  pow((pt1.getZ() - pt2.getZ()), 2));
}
