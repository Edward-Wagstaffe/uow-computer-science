#include "gridStruct.h"

#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

// non default constructor for the Grid
// Initializes the coordinate boundaries and the string 2D array
Grid::Grid(int xval, int Xval, int yval, int Yval)
{
    minX = xval;
    maxX = Xval;
    minY = yval;
    maxY = Yval;

    rows = maxY - minY + 1;
    cols = maxX - minX + 1;
    area = rows * cols;

    // Allocates the 2D array based on the input from the config file
    array2D = new string*[rows];
    for (int i = 0; i < rows; i++)
    {
        array2D[i] = new string[cols];
    }
}
// Deconstructor
// deallocates the dynamically allocated 2D array
Grid::~Grid()
{
    for (int i = 0; i < rows; i++)
    {
        delete[] array2D[i];
    }
    delete[] array2D;
    cout << "deallocated array2D" << endl;
}
// Generates the string representation of the Grid
string Grid::displayGrid() const
{
    ostringstream oss;
    const int BORDER_WIDTH = 4;
    const int CELL_WIDTH = 3;

    oss << endl;

    // top border
    oss << right << setw(BORDER_WIDTH) << " ";
    for (int i = 0; i < cols + 2; i++)
    {
        oss << "#  ";
    }
    oss << endl;

    // loop so that the origin is bottom left.
    for (int y = maxY; y >= minY; y--)
    {
        int rowIdx = y - minY;
        // Y-axis index
        oss << setw(BORDER_WIDTH - 1) << y << " #";
        for (int x = minX; x <= maxX; x++)
        {
            int colIdx = x - minX;
            // Print content if the cell is not empty, else print a space.
            if (!array2D[rowIdx][colIdx].empty())
                oss << setw(CELL_WIDTH) << array2D[rowIdx][colIdx];
            else
                oss << setw(CELL_WIDTH) << " ";
        }
        oss << "  #\n";
    }

    // bottom border
    oss << setw(BORDER_WIDTH) << " ";
    for (int i = 0; i < cols + 2; i++)
    {
        oss << "#  ";
    }
    oss << endl;

    oss << setw(BORDER_WIDTH + 1) << "";
    for (int x = minX; x <= maxX; x++)
    {  // X-axis index
        oss << setw(CELL_WIDTH) << x;
    }
    oss << endl << endl;

    return oss.str();
}
// clears the grid without deallocating the array.
void Grid::clear2DArray()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) array2D[i][j].clear();
}
