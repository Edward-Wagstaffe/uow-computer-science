#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point2D
{  // friend operator overloading to support cout <<
    friend std::ostream& operator<<(std::ostream& out, Point2D& obj);

   protected:
    int x;
    int y;
    double distFrOrigin;
    // setter
    virtual void setDistFrOrigin();

   public:
    // constructors
    Point2D();              // default constructor
    Point2D(int x, int y);  // non default constructor

    // setters
    void setX(int x);
    void setY(int y);

    // getters
    double getScalarValue();
    int getX();
    int getY();

    // member function
    std::string toString();

    // member operator overloading for comparison, to sort and uniqueness check
    bool operator==(const Point2D& other) const;
    // initially used for sorting.
    bool operator<(const Point2D& other) const;
};

#endif
