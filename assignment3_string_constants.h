/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#ifndef ASSIGNMENT3_STRING_CONSTANTS_H_
#define ASSIGNMENT3_STRING_CONSTANTS_H_

#include <string>

using namespace std;

const string kGetFile = "Please enter in the name of a code file whose delimiter syntax is to be verified: ";
const string kGetFileNoCmdlArg = "\nNo command line argument was provided!\n" + kGetFile;
const string kBadFileName = "\nThe provided file name does not refer to a vaild file!\nPlease try again and enter in a new code file name: ";
const string kRepeatProgram = "\nThe delimiter syntax within the code file was correct. Would you like to analyze another code file?";
const string kYes = "Yes";
const string kNo = "No";

#endif //ASSIGNMENT3_STRING_CONSTANTS_H_
