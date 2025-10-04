#include "Point2D.h"

#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

//-----------------------------------------------------------------
// Constructors
//
Point2D::Point2D() {}

Point2D::Point2D(int x, int y)
{
    this->x = x;
    this->y = y;
    setDistFrOrigin();
}

//------------------------------------------------------------------
// Operator Overloading, friend and member functions
ostream& operator<<(ostream& out, Point2D& obj)
{
    out << obj.toString();
    return out;
}
bool Point2D::operator==(const Point2D& other) const
{
    return (x == other.x) && (y == other.y);
}

bool Point2D::operator<(const Point2D& other) const
{
    return (x < other.x) || (x == other.x && y < other.y);
}
//-------------------------------------------------------------------
// Member function

string Point2D::toString()
{
    ostringstream oss;
    oss << "[" << right << setw(4) << x << ", " << right << setw(4) << y << "]" << "   " << fixed
        << setprecision(3) << distFrOrigin;
    return oss.str();
}

//------------------------------------------------------------------
// Getters
double Point2D::getScalarValue()
{
    return distFrOrigin;
}

int Point2D::getX()
{
    return x;
}

int Point2D::getY()
{
    return y;
}

//--------------------------------------------------------------------
// Setters
void Point2D::setX(int x)
{
    this->x = x;
}

void Point2D::setY(int y)
{
    this->y = y;
}

void Point2D::setDistFrOrigin()
{
    distFrOrigin = sqrt((x * x) + (y * y));
}
