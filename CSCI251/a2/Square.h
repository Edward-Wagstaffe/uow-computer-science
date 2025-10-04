#ifndef SQUARE_H
#define SQUARE_H

#include "Point.h"
#include "ShapeTwoD.h"
using namespace std;

class Square : public ShapeTwoD
{
    friend ostream& operator<<(ostream& sOut, Square& obj);
    friend istream& operator>>(istream& sIn, Square& obj);

   private:
    vector<Point> vertices;

   public:
    Square();                     // default
    Square(string nm, bool cWS);  // non default

    virtual string toString() override;
    virtual double computeArea() const override;
    virtual bool isPointInShape(int x, int y) const override;
    virtual bool isPointOnShape(int x, int y) const override;

    virtual vector<Point> getEnclosingPoints() override;
    virtual vector<Point> getPointsInShape() override;
    virtual vector<Point> getPointsOnShape() override;

    bool isSquare();
};

#endif
