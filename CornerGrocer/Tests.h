#ifndef TESTS_H
#define TESTS_H

#include "ItemTracker.h"

/*
    Author: Rick Goshen
    Date: 02/22/2025
    Purpose: Defines automated tests for ItemTracker, ensuring correct functionality.
             Tests run automatically before the main program to validate item frequency
             tracking, case sensitivity handling, file output correctness, and input validation.
*/

// Runs item frequency tests using a separate test input file
bool testItemFrequency();

// Runs plural-to-singular and singular-to-plural tests
bool testPluralSingularMatching();

// Runs tests for handling invalid data (numbers & special characters)
bool testInvalidDataHandling();

// Runs file backup validation tests
bool testBackupFileCreation();

// Runs string normalization tests
bool testStringNormalizer();

// Runs a test for integer values (item frequencies)
bool runTest(const std::string& testName, int expected, int actual);

// Runs a test for string values (string normalization & plural/singular matching)
bool runTestString(const std::string& testName, const std::string& expected, const std::string& actual);

// Runs all test cases before launching the program
void runAllTests();

#endif // TESTS_H