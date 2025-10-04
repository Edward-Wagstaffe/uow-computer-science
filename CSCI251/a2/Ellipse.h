#ifndef ELLIPSE_H
#define ELLIPSE_H

#include <vector>

#include "Point.h"
#include "ShapeTwoD.h"
using namespace std;

class Ellipse : public ShapeTwoD
{
    friend ostream& operator<<(ostream& sOut, Ellipse& obj);
    friend istream& operator>>(istream& sIn, Ellipse& obj);

   private:
    Point center;
    int xRadius;
    int yRadius;

   public:
    Ellipse();
    Ellipse(string nm, bool cWS);

    virtual string toString() override;
    virtual double computeArea() const override;
    virtual bool isPointInShape(int x, int y) const override;
    virtual bool isPointOnShape(int x, int y) const override;

    virtual vector<Point> getEnclosingPoints() override;
    virtual vector<Point> getPointsOnShape() override;
    virtual vector<Point> getPointsInShape() override;
};

#endif
