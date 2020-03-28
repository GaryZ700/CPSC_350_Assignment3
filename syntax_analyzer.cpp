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
	this->leftDelimiters = new GenStack<char>();
	this->rightDelimiters = new GenStack<char>();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*SyntaxAnalyzer Deconstructor Function*/
SyntaxAnalyzer::~SyntaxAnalyzer(){
	delete leftDelimiters;
	delete rightDelimiters;
	delete reverseRightDelimiters;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Analyze Method
  Returns a bool representing whether the delmiter syntax in the provided file is correct
  codeFile: fstream to the code file to analyze*/
bool SyntaxAnalyzer::Analyze(fstream &codeFile){

	char testChar;
	
	while(codeFile.get(testChar))
		AddDelimiter(testChar);

	//reverse the right side delimiters
	reverseRightDelimiters = ReverseDelimiterStack(*rightDelimiters);

	//analyze the delimiters to ensure that there are no syntax errors
	while(!leftDelimiters->Empty()){
		cout << leftDelimiters->Pop() << endl; 
	} 
	
	return true;
}

//---------------------------------------------------------------------------------

/*AddDelmiter Method
  Has a void return
  testChar: char representing the character to add as a delimiter*/
void SyntaxAnalyzer::AddDelimiter(char testChar){

	int delimiterCode = IsDelimiter(testChar);

	if(delimiterCode == 0)
		rightDelimiters->Push(testChar);	
	else if(delimiterCode == 1)
		leftDelimiters->Push(testChar);
}

//---------------------------------------------------------------------------------

/*IsDelimiter Method
  Returns an int representing whether the specified char is an invalid delmiter, or a left or right side delmiter
	-1 = Invalid Delimiter 
	 1 = Right Side Delimiter
	 0 = Left Side Delimiter
  testChar: char that is to be tested to determine if it is a delimiter*/
int SyntaxAnalyzer::IsDelimiter(char testChar){

	int index = 2;
	int lastIndex;

	//perform a binary search on the delimiters string in order to check if the test char is a valid delmiter
	while(index >= 0 && index <= 5 && lastIndex != index){

		//get last index every other cycle to check if 
		//there is an inbetween value that results in
		//"bouncing "between two indexes 
		if(index %2 == 0)
			lastIndex = index;

		if(testChar == delimiters[index]){
			return index % 2;
		}
		else if(testChar > delimiters[index])
			++index;
		else 
			--index;
	}

	return -1;
}

//---------------------------------------------------------------------------------

/*ReverseDelimiterStack Methods
  Returns a pointer to a reversed char GenStack
  delimiterStack: char GenStack that is to be reversed, is pass by copy to allow the reversal occur without affecting the original stack object*/
GenStack<char> * SyntaxAnalyzer::ReverseDelimiterStack(GenStack<char> delimiterStack){
	
	GenStack<char> *reversedDelimiterStack = new GenStack<char>(delimiterStack.Size());
	
	while(!delimiterStack.Empty())	
		reversedDelimiterStack->Push(delimiterStack.Pop());

	return reversedDelimiterStack;
}
