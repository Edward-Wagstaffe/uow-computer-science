#ifndef LINE2D_H
#define LINE2D_H

#include <iostream>

#include "Point2D.h"
class Line2D
{
    // friend operator overloading to support cout <<
    friend std::ostream& operator<<(std::ostream& out, Line2D& obj);

   private:
    Point2D pt1;
    Point2D pt2;

   protected:
    double length;
    // setter
    virtual void setLength();

   public:
    // constructors
    Line2D();
    Line2D(Point2D pt1, Point2D pt2);

    // getters
    Point2D getPt1();
    Point2D getPt2();
    double getScalarValue();

    // setters
    void setPt1(Point2D pt1);
    void setPt2(Point2D pt2);

    // member function
    std::string toString();
    // member operator overloading for comparison to sort and uniqueness check
    bool operator==(const Line2D& other) const;
};

#endif
