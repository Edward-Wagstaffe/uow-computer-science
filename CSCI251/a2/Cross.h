#ifndef CROSS_H
#define CROSS_H

#include "Point.h"
#include "ShapeTwoD.h"
using namespace std;

class Cross : public ShapeTwoD
{
    friend ostream& operator<<(ostream& sOut, Cross& obj);
    friend istream& operator>>(istream& sIn, Cross& obj);

   private:
    vector<Point> vertices;

   public:
    Cross();
    Cross(string nm, bool cWS);

    virtual string toString() override;
    virtual double computeArea() const override;
    virtual bool isPointInShape(int x, int y) const override;
    virtual bool isPointOnShape(int x, int y) const override;

    virtual vector<Point> getEnclosingPoints() override;
    virtual vector<Point> getPointsInShape() override;
    virtual vector<Point> getPointsOnShape() override;

    bool isCross();
};

#endif
