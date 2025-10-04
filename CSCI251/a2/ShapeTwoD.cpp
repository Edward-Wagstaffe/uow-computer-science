#include "ShapeTwoD.h"

#include <sstream>
#include <string>

int ShapeTwoD::nextID = 0;  // rolling ID to store shape ID

// operator overloading
ostream& operator<<(ostream& sOut, ShapeTwoD& obj)  // #elegance
{
    sOut << obj.toString();
    return sOut;
}

//--------------------------------------------------------
// constructors
ShapeTwoD::ShapeTwoD()  // default constructor
{
    id = nextID++;
    area = 0;
}

ShapeTwoD::ShapeTwoD(string nm, bool cWS)  // non default constructor
{
    name = nm;
    containsWarpSpace = cWS;
    id = nextID++;
    area = 0;
}

//--------------------------------------------------------
// virtual functions
// since ShapeTwoD is not an abstract class, these must be implemented.
string ShapeTwoD::toString()
{
    ostringstream oss;
    oss << "Shape[" << id << "]" << endl;
    oss << "Name: " << name << endl
        << "Special Type: " << (getContainsWarpSpace() ? "WS" : "NS") << endl;
    return oss.str();
}
double ShapeTwoD::computeArea() const
{
    return 0;
}
bool ShapeTwoD::isPointInShape(int x, int y) const
{
    return false;
}
bool ShapeTwoD::isPointOnShape(int x, int y) const
{
    return false;
}

vector<Point> ShapeTwoD::getEnclosingPoints()
{
    vector<Point> empty;
    return empty;
}
vector<Point> ShapeTwoD::getPointsOnShape()
{
    vector<Point> empty;
    return empty;
}

vector<Point> ShapeTwoD::getPointsInShape()
{
    vector<Point> empty;
    return empty;
}

//--------------------------------------------------------
// getters
string ShapeTwoD::getName()
{
    return name;
}

bool ShapeTwoD::getContainsWarpSpace()
{
    return containsWarpSpace;
}

double ShapeTwoD::getArea()
{
    return area;
}

//--------------------------------------------------------
// setters
void ShapeTwoD::setName(string newName)
{
    name = newName;
}
void ShapeTwoD::setContainsWarpSpace(bool newCWS)
{
    containsWarpSpace = newCWS;
};

void ShapeTwoD::setArea(double newArea)
{
    area = newArea;
}
