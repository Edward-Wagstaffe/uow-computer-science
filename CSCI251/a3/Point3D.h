#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"
class Point3D : public Point2D
{
    // friend operator overloading to support cout <<
    friend std::ostream& operator<<(std::ostream& out, Point3D& obj);

   protected:
    int z;
    // setter
    virtual void setDistFrOrigin() override;

   public:
    // constructors
    Point3D();
    Point3D(int x, int y, int z);

    // getters
    int getZ();

    // setters
    void setZ(int z);

    // member function
    std::string toString();

    // member operator overloading for comparison, to sort and uniquenes check
    bool operator==(const Point3D& other) const;
};

#endif
