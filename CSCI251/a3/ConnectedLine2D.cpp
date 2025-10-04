#include "ConnectedLine2D.h"

#include <iomanip>
#include <sstream>

#include "Line2D.h"

using namespace std;

//-----------------------------------------------------------------
// Constructors
//
ConnectedLine2D::ConnectedLine2D() {};
ConnectedLine2D::ConnectedLine2D(Line2D l1, Line2D l2)
{
    line1 = l1;
    line2 = l2;
    setTotalLength();
}

//------------------------------------------------------------------
// Operator Overloading, friend and member functions
ostream& operator<<(ostream& out, ConnectedLine2D& obj)
{
    out << obj.toString();
    return out;
}

bool ConnectedLine2D::operator==(const ConnectedLine2D& other) const
{
    return (line1 == other.line1 && line2 == other.line2) ||
           (line1 == other.line2 && line2 == other.line1);
}

//-------------------------------------------------------------------
// Member function
string ConnectedLine2D::toString()
{
    ostringstream oss;
    oss << "[" << right << setw(4) << line1.getPt1().getX() << ", " << right << setw(4)
        << line1.getPt1().getY() << "]   ";
    oss << "[" << right << setw(4) << line1.getPt2().getX() << ", " << right << setw(4)
        << line1.getPt2().getY() << "]   ";
    oss << "[" << right << setw(4) << line2.getPt2().getX() << ", " << right << setw(4)
        << line2.getPt2().getY() << "]   ";
    oss << fixed << setprecision(3) << length;
    return oss.str();
}

//------------------------------------------------------------------
// Getters
Line2D ConnectedLine2D::getLine1()
{
    return line1;
}

Line2D ConnectedLine2D::getLine2()
{
    return line2;
}

double ConnectedLine2D::getTotalLength()
{
    return length;
}

//--------------------------------------------------------------------
// Setters
void ConnectedLine2D::setTotalLength()
{
    length = line1.getScalarValue() + line2.getScalarValue();
}
