#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "ShapeTwoD.h"
using namespace std;

class Rectangle : public ShapeTwoD
{
    friend ostream& operator<<(ostream& sOut, Rectangle& obj);
    friend istream& operator>>(istream& sIn, Rectangle& obj);

   private:
    vector<Point> vertices;

   public:
    Rectangle();
    Rectangle(string nm, bool cWS);

    virtual string toString() override;
    virtual double computeArea() const override;
    virtual bool isPointInShape(int x, int y) const override;
    virtual bool isPointOnShape(int x, int y) const override;

    virtual vector<Point> getEnclosingPoints() override;
    virtual vector<Point> getPointsOnShape() override;
    virtual vector<Point> getPointsInShape() override;

    bool isRectangle();
};

#endif
