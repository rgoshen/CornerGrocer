#include "ItemTracker.h"
#include <algorithm> // For transform (case normalization)
#include <iostream>
#include <fstream>

/*
    Author: Rick Goshen
    Date: 02/22/2025
    Purpose: Implements the ItemTracker class to read a file, count item occurrences,
             and provide various output formats including frequency reports and histograms.
             This class ensures case insensitivity and corrects minor input errors
             (e.g., "apple" -> "apples").
*/

ItemTracker::ItemTracker(const string& filename, const string& outputFilename)
    : inputFile(filename), outputFile(outputFilename) {
    loadItemsFromFile();
    saveFrequencyToFile();
}

void ItemTracker::loadItemsFromFile() {
    ifstream file(inputFile);
    string item;

    if (!file) {
        cerr << "Error: Unable to open file " << inputFile << endl;
        exit(EXIT_FAILURE);
    }

    while (file >> item) {
        item = normalizeString(item);  // Convert to lowercase

        // Validate: Only allow alphabetic words
        if (all_of(item.begin(), item.end(), ::isalpha)) {
            itemFrequency[item]++;
        }
    }

    file.close();
}

void ItemTracker::saveFrequencyToFile() {
    ofstream outFile(outputFile, ios::trunc);
    if (!outFile) {
        cerr << "Error: Unable to create file " << outputFile << endl;
        exit(EXIT_FAILURE);
    }

    for (const auto& pair : itemFrequency) {
        outFile << pair.first << " " << pair.second << endl;
    }

    outFile.close();
}

/*
    Finds the closest match for an item if the exact match is not found.
    This helps users when they enter singular/plural variations of an item.
*/
string ItemTracker::getClosestMatch(const string& userInput) const {
    if (userInput.empty()) {
        return ""; // Prevent accessing .back() on an empty string
    }

    string normalizedInput = normalizeString(userInput); // Ensure lowercase input

    // If the exact word exists, return it directly
    if (itemFrequency.find(normalizedInput) != itemFrequency.end()) {
        return normalizedInput;
    }

    // Iterate over itemFrequency to check for singular/plural conversion
    for (const auto& pair : itemFrequency) {
        string storedItem = pair.first;
        string normalizedStoredItem = normalizeString(storedItem);

        // Handle standard plural cases (e.g., "apple" -> "apples", "carrot" -> "carrots")
        if (normalizedStoredItem == normalizedInput + "s" || normalizedStoredItem == normalizedInput + "es") {
            return storedItem;  // Return the original case-sensitive stored item
        }
    }

    return ""; // No match found
}

/*
    Retrieves the purchase frequency of an item.
    If an exact match is found, it returns the count.
    If not, it suggests the closest valid match (e.g., "apple" -> "apples").
*/
int ItemTracker::getItemFrequency(const string& item) const {
    string normalizedItem = normalizeString(item);
    auto it = itemFrequency.find(normalizedItem);

    if (it != itemFrequency.end()) {
        return it->second;
    }
    else {
        // Check for closest match (e.g., "apple" -> "apples")
        string closestMatch = getClosestMatch(normalizedItem);
        if (!closestMatch.empty()) {
            cout << "\nDid you mean \"" << closestMatch << "\"? Showing results for " << closestMatch << ".\n";
            return itemFrequency.at(closestMatch);
        }
    }

    return 0;
}

void ItemTracker::displayAllItems() const {
    for (const auto& pair : itemFrequency) {
        cout << pair.first << " " << pair.second << endl;
    }
}

void ItemTracker::displayHistogram() const {
    for (const auto& pair : itemFrequency) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; ++i) {
            cout << "*";
        }
        cout << endl;
    }
}

/*
    Normalizes a string to lowercase.
    Ensures case-insensitive matching of items.
*/
string normalizeString(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}