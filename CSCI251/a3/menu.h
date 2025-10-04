#ifndef MENU_H
#define MENU_H

#include <iostream>
void displayMenuOptions();
void handleReadInData();
void displayFilteringCriteriaMenu();

void displaySortingCriteriaMenu1();
void displaySortingCriteriaMenu2();
void displaySortingCriteriaMenu3();
void displaySortingCriteriaMenu4();

void handleSpecifyingFilteringCriteria();

void handleSortingCriteria();
void getSortingCriteria1();
void getSortingCriteria2();
void getSortingCriteria3();
void getSortingCriteria4();

void handleSortingOrder();
void displaySortingOrderMenu();

void handleViewData();
void handleStoreData();

extern std::string filterCriteria;
extern std::string sortingCriteria;
extern std::string sortingOrder;

void pressEnterToContinue();

#endif
