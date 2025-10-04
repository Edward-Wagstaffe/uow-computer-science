
#include "shapeManager.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "Circle.h"
#include "Cross.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "ShapeTwoD.h"
#include "Square.h"
#include "utils.h"

// Global array of pointers to store any derived ShapeTwoD.
vector<ShapeTwoD*> shapeList;

// prompts user for shape details and initializes them if no exceptions are thrown.
// The shape object is appended to the global array.
void promptShapeType()
{
    string name;
    string specialType;
    bool validUserInput = false;
    while (!validUserInput)
    {
        try
        {
            cout << "Please enter name of shape: ";
            cin >> name;

            name = trim(name);
            name = toUpper(name);
            validateName(name);  // ensure name is one of the available shapes.

            cout << "Please enter special type: ";
            cin >> specialType;

            specialType = trim(specialType);
            specialType = toUpper(specialType);
            validateSpecialType(specialType);  // ensure special type is either WS or NS

            bool containsWarpSpace = (specialType == "WS");

            if (name == "SQUARE")
            {
                Square* newSquare = new Square("Square", containsWarpSpace);
                cin >> *newSquare;
                shapeList.push_back(newSquare);
            }
            else if (name == "RECTANGLE")
            {
                Rectangle* newRectangle = new Rectangle("Rectangle", containsWarpSpace);
                cin >> *newRectangle;
                shapeList.push_back(newRectangle);
            }
            else if (name == "CROSS")
            {
                Cross* newCross = new Cross("Cross", containsWarpSpace);
                cin >> *newCross;
                shapeList.push_back(newCross);
            }
            else if (name == "CIRCLE")
            {
                Circle* newCircle = new Circle("Circle", containsWarpSpace);
                cin >> *newCircle;
                shapeList.push_back(newCircle);
            }
            else if (name == "ELLIPSE")
            {
                Ellipse* newEllipse = new Ellipse("Ellipse", containsWarpSpace);
                cin >> *newEllipse;
                shapeList.push_back(newEllipse);
            }
            validUserInput = true;
        }
        catch (const invalid_argument& e)
        {
            cout << endl;
            cout << "Error: " << e.what() << endl;
            cout << "Please try again..." << endl << endl;
        }
        catch (ShapeTwoD obj)
        {
            cout << endl;
            cout << "Error: Invalid vertices for " << name << " type!" << endl;
            cout << "Please try again..." << endl << endl;
        }
    }
}

// Validates the shape name, ensures that it is one of the implemented types
void validateName(const string& name)
{
    vector<string> validNames = {"CIRCLE", "SQUARE", "RECTANGLE", "CROSS", "ELLIPSE"};
    if (find(validNames.begin(), validNames.end(), name) == validNames.end())
    {
        throw invalid_argument("Invalid name: " + name);
    }
}

// Validates the special type, ensures that it is either WS or NS
void validateSpecialType(const string& specialType)
{
    if (!(specialType == "NS" || specialType == "WS"))
    {
        throw invalid_argument("Invalid Special Type: " + specialType);
    }
}

// Print shapes using polymorphism
void printShapes()
{
    for (int i = 0; i < shapeList.size(); i++)
    {
        cout << *shapeList[i] << endl << endl;
    }
}

// frees any dynamically allocated memory
void deallocateSafely()
{
    for (int i = 0; i < shapeList.size(); i++)
    {
        delete shapeList[i];
    }
    cout << "deallocated shapeList" << endl;
}

// update area for those that have not yet been calculated
void updateArea()
{
    int counter = 0;
    for (int i = 0; i < shapeList.size(); i++)
    {
        if (!(shapeList[i]->getArea()))
        {
            shapeList[i]->setArea(shapeList[i]->computeArea());
            counter++;
        }
    }
    cout << endl << "Computation completed! (" << counter << " records were updated)" << endl;
}

// sorts entire array by area, ascending.
void sortAllByAreaAscending(vector<ShapeTwoD*> sortedList)
{
    sort(sortedList.begin(), sortedList.end(),
         [](ShapeTwoD* a, ShapeTwoD* b) { return a->getArea() < b->getArea(); });

    for (int i = 0; i < sortedList.size(); i++)
    {
        cout << *sortedList[i] << endl << endl;  // uses polymorphism
    }
}

// sorts entire array by area, descending
void sortAllByAreaDescending(vector<ShapeTwoD*> sortedList)
{
    sort(sortedList.begin(), sortedList.end(),
         [](ShapeTwoD* a, ShapeTwoD* b) { return a->getArea() > b->getArea(); });

    for (int i = 0; i < sortedList.size(); i++)
    {
        cout << *sortedList[i] << endl << endl;  // uses polymorphism
    }
}

// Sorts by special type, showing those that are WS first, then NS. secondary sorting by area
// descending.
void sortBySpecialType()
{
    // split global array into two temp arrays, sort by WS and NS type.
    vector<ShapeTwoD*> WStype;
    vector<ShapeTwoD*> NStype;
    for (int i = 0; i < shapeList.size(); i++)
    {
        if (shapeList[i]->getContainsWarpSpace())
        {
            WStype.push_back(shapeList[i]);  // append all WS types
        }
        else
        {
            NStype.push_back(shapeList[i]);  // append all NS types
        }
    }

    // secondary sorting by area descending, displaying WS first
    sortAllByAreaDescending(WStype);
    sortAllByAreaDescending(NStype);
}
