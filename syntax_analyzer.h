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
#include <regex>
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
		GenStack<char> *rightDelimiters;
		GenStack<char> *reverseRightDelimiters;
		
		void AddDelimiter(char testChar);
		int IsDelimiter(char testChar);
		GenStack<char>* ReverseDelimiterStack(GenStack<char> delimiterStack);
};

#endif //SYNTAX_ANALYZER_H_
