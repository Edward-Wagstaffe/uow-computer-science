#include <iostream>

#include "menu.h"

using namespace std;
int main()
{
    int usersChoice = 0;  // stores users menu choice (1-7)

    do
    {
        displayMenuOptions();
        cin >> usersChoice;  // get the users choice.
        cout << endl;

        switch (usersChoice)
        {
            case 1:
                handleReadInData();  // load data from file
                break;
            case 2:
                handleSpecifyingFilteringCriteria();  // choose type of object to filter by
                pressEnterToContinue();
                break;
            case 3:
                handleSortingCriteria();  // choose sorting criteria
                pressEnterToContinue();
                break;
            case 4:
                handleSortingOrder();  // choose asecnding / descending
                pressEnterToContinue();
                break;
            case 5:
                handleViewData();  // display the formatted data output
                pressEnterToContinue();
                break;
            case 6:
                handleStoreData();  // save data to file
                pressEnterToContinue();
                break;
            case 7:
                cout << "Goodbye!" << endl;  // exit
                break;
        }

    } while (usersChoice != 7);  // loop til user chooses 7
    return 0;
}
