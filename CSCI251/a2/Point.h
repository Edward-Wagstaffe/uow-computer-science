#ifndef POINT_H
#define POINT_H

#include <string>

using namespace std;

class Point
{
    friend ostream& operator<<(ostream& sOut, Point& obj);

   public:
    int x;
    int y;

    Point();
    Point(int xVal, int yVal);

    string toString();

    bool operator<(const Point& rhs);
};

#endif
