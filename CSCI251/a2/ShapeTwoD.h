#ifndef SHAPETWOD_H
#define SHAPETWOD_H

#include <string>
#include <vector>

#include "Point.h"

using namespace std;

class ShapeTwoD
{
    friend ostream& operator<<(ostream& sOut,
                               ShapeTwoD& obj);  // overload the insertion operator for elegance :)
   protected:
    static int nextID;  // class variable
    int id;
    string name;
    bool containsWarpSpace;
    double area;

   public:
    ShapeTwoD();                     // default constructor
    ShapeTwoD(string nm, bool cWS);  // non default constructor

    // required virtual member functions
    virtual string toString();
    virtual double computeArea() const;
    virtual bool isPointInShape(int x, int y) const;
    virtual bool isPointOnShape(int x, int y) const;

    // extra
    virtual vector<Point> getEnclosingPoints();
    virtual vector<Point> getPointsOnShape();
    virtual vector<Point> getPointsInShape();

    // getters
    string getName();
    bool getContainsWarpSpace();
    double getArea();

    // setters
    void setName(string name);
    void setContainsWarpSpace(bool containsWarpSpace);
    void setArea(double newArea);
};
#endif
