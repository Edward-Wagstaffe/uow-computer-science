#ifndef CONNECTEDLINE2D_H
#define CONNECTEDLINE2D_H

#include <iostream>

#include "Line2D.h"

class ConnectedLine2D
{  // friend operator overloading to support cout<<
    friend std::ostream& operator<<(std::ostream& out, ConnectedLine2D& obj);

   private:
    Line2D line1;
    Line2D line2;

   protected:
    double length;
    // setter
    void setTotalLength();

   public:
    // constructors
    ConnectedLine2D();
    ConnectedLine2D(Line2D l1, Line2D l2);

    // getters
    Line2D getLine1();
    Line2D getLine2();
    double getTotalLength();

    // member functions
    std::string toString();

    // member overloading to support comparison for sorting and uniqueness check
    bool operator==(const ConnectedLine2D& other) const;
};
#endif
