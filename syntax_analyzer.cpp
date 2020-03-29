/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#include "syntax_analyzer.h"

using namespace std;

/*Syntax Analyzer Constructor*/
SyntaxAnalyzer::SyntaxAnalyzer(){
	this->leftDelimiters = new GenStack<char>;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*SyntaxAnalyzer Deconstructor Function*/
SyntaxAnalyzer::~SyntaxAnalyzer(){
	delete leftDelimiters;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Analyze Method
  Returns a bool representing whether the delmiter syntax in the provided file is correct
  codeFile: fstream to the code file to analyze*/
bool SyntaxAnalyzer::Analyze(fstream &codeFile){
	
	bool correctSyntax = true;
	int lineNumber = 1;
	int delimiterCode;
	char codeChar;

	codeFile.get(codeChar);
		
	do{	
		delimiterCode = IsDelimiter(codeChar);
	 
		//check whether or not a delimiter is being delt with
		if(delimiterCode == -1){
			if(codeChar == '\n')
				++lineNumber;
			continue;
		}

		correctSyntax = CoreLogic(codeChar, delimiterCode, lineNumber); 
		
	}while( correctSyntax && codeFile.get(codeChar));

	//Case where there is a starting delimiter with no ending delmiter, ex. Has '[' but missing ']'
	if(correctSyntax && leftDelimiters->Size() > 0)
		correctSyntax = ErrorMessage(leftDelimiters->Pop(), ' ', lineNumber);

	
	return correctSyntax;
}

//---------------------------------------------------------------------------------

/*DelimiterSearch Method
  Has a void return
  codeChar: pass by reference char that represents the code char to search for
  delimiterCode: int that represents the type of delimiter found: 
	-1 = Invalid Delimiter 
	 1 = Right Side Delimiter
	 0 = Left Side Delimiter
  index: pass by refernce integer that represents the location of the code char in the delimiters array*/
void SyntaxAnalyzer::DelimiterSearch(char codeChar, int &delimiterCode, int &index){
	
	delimiterCode = -1;
	index = 2;
	int lastIndex = -1;

	//perform a binary search on the delimiters string in order to check if the test char is a valid delmiter
	while(index >= 0 && index <= 5 && lastIndex != index){

		 //get last index every other cycle to check if 
		//there is an inbetween value that results in
		//"bouncing" between two indexes 
		if(index %2 == 0)
			lastIndex = index;

		if(codeChar == delimiters[index]){
			 delimiterCode = index % 2;
			 return;
		}
		else if(codeChar > delimiters[index])
			++index;
		else 
			--index;
	}
}

//---------------------------------------------------------------------------------

/*IsDelimiter Method
  Returns an int representing whether the specified char is an invalid delmiter, or a left or right side delmiter
	-1 = Invalid Delimiter 
	 1 = Right Side Delimiter
	 0 = Left Side Delimiter
  codeChar: char that is to be tested to determine if it is a delimiter*/
int SyntaxAnalyzer::IsDelimiter(char codeChar){

	int delimiterCode;
	int index;
	
	DelimiterSearch(codeChar, delimiterCode, index);

	return delimiterCode;
}

//---------------------------------------------------------------------------------

/*OppositeDelimiter Method
  Returns a char that is the opposite delimiter for the provided codeChar, returns -1 if invalid delimiter is provided
  codeChar: delimiterChar whose opposite is to be found*/
char SyntaxAnalyzer::OppositeDelimiter(char codeChar){
	
	int delimiterCode;
	int index;

	DelimiterSearch(codeChar, delimiterCode, index);

	return delimiters[index + (1 - 2*delimiterCode)];
}

//---------------------------------------------------------------------------------

/*CoreLogic Function, has main core logic for determining if there is a delimiter syntax error
  Returns a bool representing whether or not there is a delimiter syntax error present in the code
  */
bool SyntaxAnalyzer::CoreLogic(char codeChar, int delimiterCode, int lineNumber){
	
	//for left side delimiters
	if(delimiterCode == 0)
		leftDelimiters->Push(codeChar);

	//for right side delimiters
	else if(delimiterCode == 1){

		//case where there is a right delimiter with no left delimiter, ex. a random ']' without a starting '['		
		if(leftDelimiters->Empty())
			return ErrorMessage(' ', codeChar, lineNumber);
	
		//case where expecting a certain ending delimiter but another is found, ex. expecting ']' but found '}' instead	
		char leftDelimiter = leftDelimiters->Pop();
		if(codeChar != OppositeDelimiter(leftDelimiter))
			return ErrorMessage(leftDelimiter, codeChar, lineNumber); 
	}

	return true;
}

//---------------------------------------------------------------------------------

/*ErrorMessage Function 
  Always returns false to represent that a syntax error was found
  leftDelimiter: char that represents the left delimiter
  rightDelimiter: char that represents the right delimiter
  lineNumber: int that represents the line where the error occured
*/
bool SyntaxAnalyzer::ErrorMessage(char leftDelimiter, char rightDelimiter, int lineNumber){

	cout << endl;
		
	if(rightDelimiter == ' ')
		cout << "Error, End of File Reached: Expecting '" << OppositeDelimiter(leftDelimiter) << "' on line " << lineNumber;
	else{
		cout << "Error, Line Number " << lineNumber << ": ";
		
		if(leftDelimiter == ' ')
			cout << "Found '" << rightDelimiter << "' without starting '" << OppositeDelimiter(rightDelimiter) << "'";
		else
			cout << ": Expecting ending delimiter for '" << leftDelimiter << "', but found '" << rightDelimiter << "'";
	}
	
	cout << "." << endl << endl;

	return false;
}
