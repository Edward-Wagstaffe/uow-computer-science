#include "menu.h"

#include <iomanip>
#include <iostream>

#include "shapeManager.h"

using namespace std;

// Displays the main menu
void displayMenuOptions()
{
    cout << endl;
    cout << left << setw(15) << "Student ID " << ": " << "8762697" << endl;
    cout << left << setw(15) << "Student Name:" << ": " << "Edward Wagstaffe" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Welcome to Assignment 2 Program!" << endl << endl;
    cout << "1) Input sensor data" << endl;
    cout << "2) Compute area (for all records)" << endl;
    cout << "3) Print shapes report" << endl;
    cout << "4) Sort shape data" << endl;
    cout << "5) Quit " << endl << endl;

    cout << "Please enter your choice (1-5) : ";
}

// displays the sub menu for sorting
void displaySubMenuOptions()
{
    cout << endl;
    cout << "a) Sort by area (ascending)" << endl;
    cout << "b) Sort by area (descending)" << endl;
    cout << "c) Sort by special type and area" << endl << endl;
    cout << "Please select sort option ('q' to go to main menu): ";
}

// Prompts user to press eneter to return to main menu.
// Clears input buffer and ensures only <enter> is accepted.
void pressEnterToContinue()
{
    // clears any previous input from the input buffer
    cin.ignore(50, '\n');
    string userInput;

    // Continuously prompts user to press Enter.
    do
    {
        cout << "\nPress <Enter> to go back to main menu";
        getline(cin, userInput);
    } while (userInput.length() != 0);
    cout << endl;
}

// handles menu option 1
void handleInputSensorData()
{
    cout << endl << "[Input Sensor Data]" << endl << endl;
    promptShapeType();
}

// handles menu option 3
void handlePrintShapes()
{
    cout << endl << "[Print Shapes Report]" << endl << endl;
    printShapes();
}

// handles menu option 5
void handleQuit()
{
    deallocateSafely();
}

// handles menu option 2
void handleComputeArea()
{
    cout << endl << "[Compute Area (for all records)]" << endl << endl;
    updateArea();
}

// handles menu option 4
void handleSortShapes()
{
    char userChoice;
    do
    {
        displaySubMenuOptions();
        cin >> userChoice;
        cout << endl;

        switch (userChoice)
        {
            case 'a':
            {
                cout << endl << "[Sort by Area smallest to largest]" << endl << endl;
                sortAllByAreaAscending(shapeList);
                pressEnterToContinue();
                break;
            }
            case 'b':
            {
                cout << endl << "[Sort by Area largest to smallest]" << endl << endl;
                sortAllByAreaDescending(shapeList);
                pressEnterToContinue();
                break;
            }
            case 'c':
            {
                cout << endl
                     << "[Sort by Special Type and Area largest to smallest]" << endl
                     << endl;
                sortBySpecialType();
                pressEnterToContinue();
                break;
            }
            case 'q':
            {
                cout << "returning to main menu" << endl;
            }
        }
    } while (userChoice != 'q');
}
