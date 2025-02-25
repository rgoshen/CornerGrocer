#include "ItemTracker.h"
#include <iostream>

using namespace std;

/*
    Author: Rick Goshen
    Date: 02/22/2025
    Purpose: Implements automated unit tests for the ItemTracker class.
             Ensures correct frequency counting, fuzzy matching (plural vs. singular),
             input validation, and file backup creation. If any test fails, the program exits.
*/

// Function to run a test for integer comparisons (used for item frequency)
bool runTest(const string& testName, int expected, int actual) {
    if (expected == actual) {
        cout << testName << " Passed\n";
        return true;
    }
    else {
        cout << testName << " Failed\n";
        cout << "  Expected: " << expected << "\n";
        cout << "  Actual: " << actual << "\n";
        return false;
    }
}

// Function to run a test for string comparisons (used for normalizeString & closest match)
bool runTestString(const string& testName, const string& expected, const string& actual) {
    if (expected == actual) {
        cout << testName << " Passed\n";
        return true;
    }
    else {
        cout << testName << " Failed\n";
        cout << "  Expected: " << expected << "\n";
        cout << "  Actual: " << actual << "\n";
        return false;
    }
}

// Tests exact item frequency matching
bool testItemFrequency() {
    cout << "\nRunning Item Frequency Tests with Test Input File:\n";

    ItemTracker testTracker("CS210_Project_Three_Test_Input.txt", "frequency_test.dat");
    bool allPassed = true;

    if (!runTest("Test: Exact Match (Apples)", 1, testTracker.getItemFrequency("apples"))) allPassed = false;
    if (!runTest("Test: Exact Match (Zucchini)", 1, testTracker.getItemFrequency("zucchini"))) allPassed = false;
    if (!runTest("Test: Non-Existent Item", 0, testTracker.getItemFrequency("XYZ"))) allPassed = false;
    if (!runTest("Test: Empty String Item", 0, testTracker.getItemFrequency(""))) allPassed = false;

    return allPassed;
}

// Tests singular/plural conversions
bool testPluralSingularMatching() {
    cout << "\nRunning Plural-Singular Matching Tests:\n";

    ItemTracker testTracker("CS210_Project_Three_Test_Input.txt", "frequency_test.dat");
    bool allPassed = true;
    string closestMatch;

    // Exact Match (word exists exactly)
    closestMatch = testTracker.getClosestMatch("apples");
    if (!runTestString("Test: Exact Match (apples) Should Return Itself", "apples", closestMatch)) allPassed = false;

    // Pluralization Handling (Singular should map to existing plural)
    closestMatch = testTracker.getClosestMatch("apple");
    if (!runTestString("Test: Singular (apple) Suggests Plural (apples)", "apples", closestMatch)) allPassed = false;

    // Words Not Found (Should return "")
    closestMatch = testTracker.getClosestMatch("tomato");
    if (!runTestString("Test: Missing Item (tomato) Should Return Empty", "", closestMatch)) allPassed = false;

    closestMatch = testTracker.getClosestMatch("zucchin");
    if (!runTestString("Test: Truncated Word (zucchin) Should Return Empty", "", closestMatch)) allPassed = false;

    // Case Sensitivity Handling
    closestMatch = testTracker.getClosestMatch("APPLE");
    if (!runTestString("Test: Uppercase Input (APPLE) Should Match (apples)", "apples", closestMatch)) allPassed = false;

    closestMatch = testTracker.getClosestMatch("ApPlEs");
    if (!runTestString("Test: Mixed Case Input (ApPlEs) Should Match (apples)", "apples", closestMatch)) allPassed = false;

    // Edge Cases (Special characters, numbers, empty input)
    closestMatch = testTracker.getClosestMatch("");
    if (!runTestString("Test: Empty String Should Return Empty", "", closestMatch)) allPassed = false;

    closestMatch = testTracker.getClosestMatch("123Oranges");
    if (!runTestString("Test: Numbers in Input (123Oranges) Should Return Empty", "", closestMatch)) allPassed = false;

    closestMatch = testTracker.getClosestMatch("@specialitem");
    if (!runTestString("Test: Special Character in Input (@specialitem) Should Return Empty", "", closestMatch)) allPassed = false;


    return allPassed;
}

// Tests handling of invalid data (numbers & special characters)
bool testInvalidDataHandling() {
    cout << "\nRunning Invalid Data Handling Tests:\n";

    ItemTracker testTracker("CS210_Project_Three_Test_Input.txt", "frequency_test.dat");
    bool allPassed = true;

    if (!runTest("Test: Numbers in Item Name (123Oranges)", 0, testTracker.getItemFrequency("123Oranges"))) allPassed = false;
    if (!runTest("Test: Special Characters in Item Name (Milk!)", 0, testTracker.getItemFrequency("Milk!"))) allPassed = false;
    if (!runTest("Test: Hashtag in Item Name (# InvalidData)", 0, testTracker.getItemFrequency("#InvalidData"))) allPassed = false;
    if (!runTest("Test: Special Character Item (@SpecialItem)", 0, testTracker.getItemFrequency("@SpecialItem"))) allPassed = false;

    return allPassed;
}

// Tests backup file creation
bool testBackupFileCreation() {
    cout << "\nRunning Backup File Creation Test:\n";

    ifstream file("frequency_test.dat");
    if (file.good()) {
        cout << "Test: Backup File Creation Passed\n";
        return true;
    }
    else {
        cout << "Test: Backup File Creation Failed\n";
        cout << "  Expected: File 'frequency_test.dat' should exist\n";
        cout << "  Actual: File was not found\n";
        return false;
    }
}

// Tests the normalizeString function
bool testStringNormalizer() {
    cout << "\nRunning String Normalizer Tests:\n";

    bool allPassed = true;

    if (!runTestString("Test: Lowercase stays lowercase", "apples", normalizeString("apples"))) allPassed = false;
    if (!runTestString("Test: Uppercase converts to lowercase", "apples", normalizeString("APPLES"))) allPassed = false;
    if (!runTestString("Test: Mixed case converts correctly", "apples", normalizeString("aPpLeS"))) allPassed = false;
    if (!runTestString("Test: Single character uppercase", "a", normalizeString("A"))) allPassed = false;
    if (!runTestString("Test: Empty string remains unchanged", "", normalizeString(""))) allPassed = false;
    if (!runTestString("Test: Special characters remain unchanged", "@123!", normalizeString("@123!"))) allPassed = false;

    return allPassed;
}

// Runs all tests and exits if any test fails
void runAllTests() {
    cout << "\nRunning Tests with a Separate Test Input File and Backup File:\n";

    bool allTestsPassed = true;

    // Run each test and check for failures
    if (!testItemFrequency()) allTestsPassed = false;
    if (!testPluralSingularMatching()) allTestsPassed = false;
    if (!testInvalidDataHandling()) allTestsPassed = false;
    if (!testStringNormalizer()) allTestsPassed = false;
    if (!testBackupFileCreation()) allTestsPassed = false;

    // If any test failed, stop execution
    if (!allTestsPassed) {
        cout << "\nERROR: One or more tests failed. The program will now exit.\n";
        exit(EXIT_FAILURE);
    }

    cout << "\nAll tests passed. Launching the program...\n";
}