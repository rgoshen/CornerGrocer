#include "ItemTracker.h"
#include "Utility.h"
#include "Tests.h"
#include <iostream>

using namespace std;

/*
    Author: Rick Goshen
    Date: 02/22/2025
    Purpose: Main driver program for the Corner Grocer's Item Tracker. Provides a menu
             allowing users to search for item frequency, display all item counts,
             view a histogram, or exit the program. Tests run automatically before execution.
*/

int main() {
    ItemTracker tracker("CS210_Project_Three_Input_File.txt");

    // Run tests before showing the menu
    runAllTests();

    cout << "\nAll tests completed. Now launching the program...\n";

    while (true) {
        cout << "\n--- Corner Grocer Menu ---\n";
        cout << "1. Look up item frequency\n";
        cout << "2. Display all items and frequencies\n";
        cout << "3. Display histogram\n";
        cout << "4. Exit\n";

        int choice = getValidatedMenuOption();

        if (choice == 1) {
            string item = getValidatedString();
            cout << "\n"; // Blank line before displaying result
            cout << item << " was purchased " << tracker.getItemFrequency(item) << " times.\n";
        }
        else if (choice == 2) {
            cout << "\n"; // Blank line before displaying result
            tracker.displayAllItems();
        }
        else if (choice == 3) {
            cout << "\n"; // Blank line before displaying result
            tracker.displayHistogram();
        }
        else {
            cout << "Exiting program...\n";
            break;
        }
    }

    return 0;
}