#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>

#include "Point.h"
#include "ShapeTwoD.h"
using namespace std;

class Circle : public ShapeTwoD
{
    friend ostream& operator<<(ostream& sOut, Circle& obj);
    friend istream& operator>>(istream& sIn, Circle& obj);

   private:
    Point center;
    int radius;

   public:
    Circle();
    Circle(string nm, bool cWS);

    virtual string toString() override;
    virtual double computeArea() const override;
    virtual bool isPointInShape(int x, int y) const override;
    virtual bool isPointOnShape(int x, int y) const override;

    virtual vector<Point> getEnclosingPoints() override;
    virtual vector<Point> getPointsOnShape() override;
    virtual vector<Point> getPointsInShape() override;
};

#endif
