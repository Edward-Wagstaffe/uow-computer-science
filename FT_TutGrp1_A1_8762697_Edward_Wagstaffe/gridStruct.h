// File: gridStruct.h

#ifndef GRIDSTRUCT_H
#define GRIDSTRUCT_H

#include <string>
using namespace std;

struct Grid
{  // min and max X and Y coordinates that define the grid bounds
    int minX;
    int maxX;
    int minY;
    int maxY;

    // rows and cols computed from the coordinate bounds above
    int rows;
    int cols;

    // number of cells in the grid (rows * cols)
    int area;

    // dyamically allocated 2D array for storing string data
    string **array2D = nullptr;

    // non default constructor
    Grid(int xval, int Xval, int yval, int Yval);
    // deconstructor
    ~Grid();

    // string representation (prints the grid)
    string displayGrid() const;
    // clears the contents of the 2Darray
    void clear2DArray();
};

#endif
