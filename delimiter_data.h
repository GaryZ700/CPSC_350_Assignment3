/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

//Struct to hold all the needed delimiter data required to perform syntax analysis on code delimiters
struct DelimiterData{
	GenStack<char> *left;
	GenStack<int> *leftLineNumbers;
	
	GenStack<char> *right;
	GenStack<int> *rightLineNumbers;
};
