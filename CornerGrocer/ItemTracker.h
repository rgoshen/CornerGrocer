#ifndef ITEM_TRACKER_H
#define ITEM_TRACKER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

/*
    Author: Rick Goshen
    Date: 02/22/2025
    Purpose: This class reads a grocery store transaction file, tracks item frequency,
             and provides options to display item counts and histograms.
             It also backs up data to a file and suggests corrections for minor input errors.
*/

class ItemTracker {
private:
    map<string, int> itemFrequency;
    string inputFile;
    string outputFile;

    void loadItemsFromFile();
    void saveFrequencyToFile();
    string getClosestMatch(const string& userInput) const; // Function to suggest correct item names

    // Allow only the specific test function to access this private method
    friend bool testPluralSingularMatching();

public:
    ItemTracker(const string& filename, const string& outputFilename = "frequency.dat");
    int getItemFrequency(const string& item) const;
    void displayAllItems() const;
    void displayHistogram() const;
};

// Function to normalize strings (convert to lowercase)
string normalizeString(const string& str);

#endif // ITEM_TRACKER_H