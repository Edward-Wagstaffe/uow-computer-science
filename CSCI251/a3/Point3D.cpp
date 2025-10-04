#include "Point3D.h"

#include <cmath>
#include <iomanip>
#include <sstream>

#include "Point2D.h"

using namespace std;

//-----------------------------------------------------------------
// Constructors
//
Point3D::Point3D() {}

Point3D::Point3D(int x, int y, int z) : Point2D(x, y)
{
    this->z = z;
    setDistFrOrigin();
}
//------------------------------------------------------------------
// Operator Overloading, friend and member functions
ostream& operator<<(ostream& out, Point3D& obj)
{
    out << obj.toString();
    return out;
}

bool Point3D::operator==(const Point3D& other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

//-------------------------------------------------------------------
// Member function
string Point3D::toString()
{
    ostringstream oss;
    oss << "[" << right << setw(4) << x << ", " << right << setw(4) << y << ", " << right << setw(4)
        << z << "]" << "   " << fixed << setprecision(3) << distFrOrigin;
    return oss.str();
}

//------------------------------------------------------------------
// Getters

int Point3D::getZ()
{
    return z;
}

//--------------------------------------------------------------------
// Setters

void Point3D::setZ(int z)
{
    this->z = z;
}
void Point3D::setDistFrOrigin()
{
    distFrOrigin = sqrt((x * x) + (y * y) + (z * z));
}
