#include <iostream>

#include "menu.h"

using namespace std;
int main()
{
    int usersChoice = 0;  // stores users menu choice (1-5)

    do
    {
        displayMenuOptions();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 1:
            {
                handleInputSensorData();  // prompt user for shape info and initalize.
                break;
            }
            case 2:
                handleComputeArea();  // Computes area for shapes that havent been computed yet.
                pressEnterToContinue();
                break;
            case 3:
                handlePrintShapes();  // Displays relevant shape info in the order that the
                                      // user entered them.
                pressEnterToContinue();
                break;
            case 4:
                handleSortShapes();  // Shows a submenu with choices to sort by area (ASC/DESC) &
                                     // special type.
                break;
            case 5:
                handleQuit();  // frees any dynamically allocated memory before quitting.
                break;
        }

    } while (usersChoice != 5);
    return 0;
}
