#ifndef LINE3D_H
#define LINE3D_H

#include "Line2D.h"
#include "Point3D.h"

class Line3D : public Line2D
{
    // friend operator overloading to support cout <<
    friend std::ostream& operator<<(std::ostream& out, Line3D& obj);

   private:
    Point3D pt1;
    Point3D pt2;

   protected:
    // setter
    virtual void setLength() override;

   public:
    // constructors
    Line3D();
    Line3D(Point3D pt1, Point3D pt2);

    // getters
    Point3D getPt1();
    Point3D getPt2();

    // setters
    void setPt1(Point3D pt1);
    void setPt2(Point3D pt2);

    // member function
    std::string toString();

    // member operator overloading for comparison to sort and uniqueness check
    bool operator==(const Line3D& other) const;
};

#endif
