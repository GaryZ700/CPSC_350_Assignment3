/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#ifndef SYNTAX_ANALYZER_H_
#define SYNTAX_ANALYZER_H_

#include <iostream>
#include <fstream>
#include "gen_stack.h"
#include "assignment3_string_constants.h"

using namespace std;

class SyntaxAnalyzer{

	public:
		SyntaxAnalyzer();
		~SyntaxAnalyzer();
		
		bool Analyze(fstream &codeFile);
	private:	
		char delimiters[6] = {'(', ')', '[', ']', '{', '}'};	
		GenStack<char> *leftDelimiters;
		
		void DelimiterSearch(char codeChar, int &delimiterCode, int &index);
		int IsDelimiter(char codeChar);
		char OppositeDelimiter(char codeChar);
		bool CoreLogic(char codeChar, int delimiterCode, int lineNumber);
		bool ErrorMessage(char leftDelimiter, char rightDelimiter, int lineNumber);
};

#endif //SYNTAX_ANALYZER_H_
