#include "menu.h"

#include <iomanip>
#include <iostream>

#include "Sorting.h"
#include "exceptionClass.h"
#include "processIOFile.h"

using namespace std;

// globals that store the current filter and sorting options. currently set to default.
string filterCriteria = "Point2D";      // default filter type
string sortingCriteria = "x-ordinate";  // default sorting crit
string sortingOrder = "ASC";            // default sorting order

// Displays the main menu
void displayMenuOptions()
{
    cout << endl;
    cout << left << setw(15) << "Student ID " << ": " << "8762697" << endl;
    cout << left << setw(15) << "Student Name:" << ": " << "Edward Wagstaffe" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Welcome to Assignment 3 Program!" << endl << endl;
    cout << "1) Read in data" << endl;
    cout << "2) Specify filtering criteria (current: " << filterCriteria << ")" << endl;
    cout << "3) Specify sorting criteria (current: " << sortingCriteria << ")" << endl;
    cout << "4) Specify sorting order (current: " << sortingOrder << ")" << endl;
    cout << "5) View data" << endl;
    cout << "6) Store data" << endl;
    cout << "7) Quit " << endl << endl;

    cout << "Please enter your choice (1-7) : ";
}

// handler function for reading in data from a file
void handleReadInData()
{
    cout << endl;
    cout << "Please enter filename: ";
    string filename;
    cin >> filename;
    try
    {
        parseFile(filename);  // calls file parser
    }

    catch (const MyException& e)
    {
        cerr << "Parse File Error: " << e.what() << endl;  // displays parsing error
    }
}

// Handler for setting sorting criteria based on the current filter.
void handleSortingCriteria()
{
    if (filterCriteria == "Point2D")
    {
        getSortingCriteria1();  // sorting options for Point2D
    }
    else if (filterCriteria == "Point3D")
    {
        getSortingCriteria2();  // sorting options for Point3D
    }
    else if (filterCriteria == "Line2D" || filterCriteria == "Line3D")
    {
        getSortingCriteria3();  // Sorting options for Line2D/3D
    }
    else if (filterCriteria == "ConnectedLine2D")
    {
        getSortingCriteria4();  // Sorting options for ConnectedLine2D
    }

    cout << "Sorting criteria successfully set to '" << sortingCriteria << "'!" << endl;
}

// handler for specifying filter criteria
void handleSpecifyingFilteringCriteria()
{
    char usersChoice;  // stores users menu choice

    do
    {
        displayFilteringCriteriaMenu();  // show filter options
        cin >> usersChoice;              // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 'a':

                // Point2D
                filterCriteria = "Point2D";
                if (sortingCriteria != "x-ordinate" && sortingCriteria != "y-ordinate" &&
                    sortingCriteria != "Dist. Fr Origin")
                {
                    sortingCriteria = "x-ordinate";  // default value
                }
                break;

            case 'b':
                // Point3D
                filterCriteria = "Point3D";
                if (sortingCriteria != "x-ordinate" && sortingCriteria != "y-ordinate" &&
                    sortingCriteria != "z-ordinate" && sortingCriteria != "Dist. Fr Origin")
                {
                    sortingCriteria = "x-ordinate";  // default value
                }
                break;
            case 'c':
                // Line2D
                filterCriteria = "Line2D";
                if (sortingCriteria != "Pt. 1" && sortingCriteria != "Pt. 2" &&
                    sortingCriteria != "Length")
                {
                    sortingCriteria = "Pt. 1";  // default value
                }
                break;
            case 'd':
                // Line3D
                filterCriteria = "Line3D";
                if (sortingCriteria != "Pt. 1" && sortingCriteria != "Pt. 2" &&
                    sortingCriteria != "Length")
                {
                    sortingCriteria = "Pt. 1";  // default value
                }
                break;
            case 'e':
                // ConnectedLine2D
                filterCriteria = "ConnectedLine2D";
                if (sortingCriteria != "Pt. 1" && sortingCriteria != "Pt. 2" &&
                    sortingCriteria != "Pt. 3" && sortingCriteria != "Total Length")
                {
                    sortingCriteria = "Pt. 1";  // default value
                }
                break;
        }

    } while (usersChoice != 'a' && usersChoice != 'b' && usersChoice != 'c' && usersChoice != 'd' &&
             usersChoice != 'e');
    cout << "Filter criteria successfully set to '" << filterCriteria << "'!" << endl;
}
//------------------------------------------------------------------------------------------------------------------------------
// Functons to get sorting criteria for different data types
// Point2D
void getSortingCriteria1()
{
    char usersChoice;  // stores users menu choice

    do
    {
        displaySortingCriteriaMenu1();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 'a':
            {
                sortingCriteria = "x-ordinate";
                break;
            }
            case 'b':
                sortingCriteria = "y-ordinate";
                break;
            case 'c':
                sortingCriteria = "Dist. Fr Origin";
                break;
        }

    } while (usersChoice != 'a' && usersChoice != 'b' && usersChoice != 'c');
}

// Point3D
void getSortingCriteria2()
{
    char usersChoice;  // stores users menu choice

    do
    {
        displaySortingCriteriaMenu2();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 'a':
            {
                sortingCriteria = "x-ordinate";
                break;
            }
            case 'b':
                sortingCriteria = "y-ordinate";
                break;
            case 'c':
                sortingCriteria = "z-ordinate";
                break;
            case 'd':
                sortingCriteria = "Dist. Fr Origin";
                break;
        }

    } while (usersChoice != 'a' && usersChoice != 'b' && usersChoice != 'c' && usersChoice != 'd');
}

// Line2D/3D
void getSortingCriteria3()
{
    char usersChoice;  // stores users menu choice

    do
    {
        displaySortingCriteriaMenu3();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 'a':
            {
                sortingCriteria = "Pt. 1";
                break;
            }
            case 'b':
                sortingCriteria = "Pt. 2";
                break;
            case 'c':
                sortingCriteria = "Length";
                break;
        }

    } while (usersChoice != 'a' && usersChoice != 'b' && usersChoice != 'c');
}

// ConnectedLine2D
void getSortingCriteria4()
{
    char usersChoice;  // stores users menu choice

    do
    {
        displaySortingCriteriaMenu4();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 'a':
            {
                sortingCriteria = "Pt. 1";
                break;
            }
            case 'b':
                sortingCriteria = "Pt. 2";
                break;
            case 'c':
                sortingCriteria = "Pt. 3";
                break;
            case 'd':
                sortingCriteria = "Total Length";
                break;
        }

    } while (usersChoice != 'a' && usersChoice != 'b' && usersChoice != 'c' && usersChoice != 'd');
}

//-----------------------------------------------------------------------------------------------------
// Menu display functions.
void displayFilteringCriteriaMenu()
{
    cout << endl;
    cout << "[Specifying filtering criteria (current: " << filterCriteria << ")]" << endl << endl;

    cout << "a) Point2D records" << endl;
    cout << "b) Point3D records" << endl;
    cout << "c) Line2D records" << endl;
    cout << "d) Line3D records" << endl;
    cout << "e) ConnectedLine2D records" << endl << endl;

    cout << "Please enter your criteria (a-e): ";
}

void displaySortingCriteriaMenu4()
{
    cout << endl;
    cout << "[Specifying sorting criteria (current: " << sortingCriteria << ")]" << endl << endl;
    cout << "a) Pt. 1's (x, y) values" << endl;
    cout << "b) Pt. 2's (x, y) values" << endl;
    cout << "c) Pt. 3's (x, y) values" << endl;
    cout << "d) Total Length value" << endl << endl;

    cout << "Please enter your criteria(a-d): ";
}
void displaySortingCriteriaMenu3()
{
    cout << endl;
    cout << "[Specifying sorting criteria (current: " << sortingCriteria << ")]" << endl << endl;
    cout << "a) Pt. 1's (x, y) values" << endl;
    cout << "b) Pt. 2's (x, y) values" << endl;
    cout << "c) Length value" << endl << endl;

    cout << "Please enter your criteria(a-c): ";
}

void displaySortingCriteriaMenu1()
{
    cout << endl;
    cout << "[Specifying sorting criteria (current: " << sortingCriteria << ")]" << endl << endl;
    cout << "a) x-ordinate value" << endl;
    cout << "b) y-ordinate value" << endl;
    cout << "c) Dist. Fr Origin value" << endl << endl;

    cout << "Please enter your criteria(a-c): ";
}

void displaySortingCriteriaMenu2()
{
    cout << endl;
    cout << "[Specifying sorting criteria (current: " << sortingCriteria << ")]" << endl << endl;
    cout << "a) x-ordinate value" << endl;
    cout << "b) y-ordinate value" << endl;
    cout << "c) z-ordinate value" << endl;
    cout << "d) Dist. Fr Origin value" << endl << endl;

    cout << "Please enter your criteria(a-d): ";
}

// Handles selecton of sorting order asc/dsc
void handleSortingOrder()
{
    char usersChoice;  // stores users menu choice

    do
    {
        displaySortingOrderMenu();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 'a':
            {
                sortingOrder = "ASC";
                break;
            }
            case 'b':
                sortingOrder = "DSC";
                break;
        }

    } while (usersChoice != 'a' && usersChoice != 'b');

    cout << "Sorting order successfully set to '" << sortingOrder << "'!" << endl;
}

// displays sorting order menu.
void displaySortingOrderMenu()
{
    cout << endl;
    cout << "[Specifying sorting order (current: " << sortingOrder << ")]" << endl << endl;
    cout << "a) ASC (Ascending order)" << endl;
    cout << "b) DSC (Descending order)" << endl << endl;

    cout << "Please enter your criteria (a-b): ";
}

// handler for viewing sorted/ filtered data.
void handleViewData()
{
    cout << endl;
    cout << "[View data...]" << endl;
    cout << "Filtering criteria: " << filterCriteria << endl;
    cout << "Sorting criteria: " << sortingCriteria << endl;
    cout << "Sorting order: " << sortingOrder << endl << endl;
    try
    {
        sortAndDisplayData();
    }
    catch (const MyException& e)
    {
        cerr << "Unable to display data: " << e.what() << endl;
    }
}

// handler for storing to a file
void handleStoreData()
{
    cout << endl;
    cout << "Please enter filename: ";
    string filename;
    cin >> filename;
    try
    {
        generateOutputFile(filename);
    }
    catch (const MyException& e)
    {
        cerr << "Unable to store data: " << e.what() << endl;
    }
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
