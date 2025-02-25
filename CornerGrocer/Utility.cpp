#include "Utility.h"

/*
    Author: Rick Goshen
    Date: 02/22/2025
    Purpose: Implements input validation for menu choices and user input.
*/

int getValidatedMenuOption() {
    int choice;
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cout << "Invalid input. Please enter a number between 1 and 4.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            return choice;
        }
    }
}

string getValidatedString() {
    string input;
    while (true) {
        cout << "Enter item name: ";
        cin >> input;

        if (!input.empty()) {
            return input;
        }
        cout << "Invalid input. Please enter a valid item name.\n";
    }
}