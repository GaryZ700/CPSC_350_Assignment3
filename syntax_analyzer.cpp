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
	this->delimiterData.left = new GenStack<char>();
	this->delimiterData.right = new GenStack<char>();
	this->delimiterData.leftLineNumbers = new GenStack<int>();
	this->delimiterData.rightLineNumbers = new GenStack<int>();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*SyntaxAnalyzer Deconstructor Function*/
SyntaxAnalyzer::~SyntaxAnalyzer(){
	delete delimiterData.left;
	delete delimiterData.right;
	delete delimiterData.leftLineNumbers;
	delete delimiterData.rightLineNumbers;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Analyze Method
  Returns a bool representing whether the delmiter syntax in the provided file is correct
  codeFile: fstream to the code file to analyze*/
bool SyntaxAnalyzer::Analyze(fstream &codeFile){

	int lineNumber = 1;
	int delimiterCode;
	char codeChar;
		
	while(codeFile.get(codeChar)){
		
		delimiterCode = IsDelimiter(codeChar);
	 
		//check whether or not the main logic applies
		if(delimiterCode == -1){
			if(codeChar == '\n')
				++lineNumber;
			continue;
		}
		
		if(CoreLogic(codeChar, delimiterCode, lineNumber) == false)
			return false;
	}

	//check if there were no ending delimiters
	if(delimiterData.left->Size() > 0){
		cout << "Error, End of File Reached: Expecting ending delimiter for '" << delimiterData.left->Pop() << "'" << endl;
		return false;
	}
	
	//run core logic again to check the last set of delimiters to ensure that they are correct	
	return true;
}

//---------------------------------------------------------------------------------

/*AddDelmiter Method
  Has a void return
  codeChar: char representing the character to add as a delimiter
  delimiterCode: int representing whether the delimiter is either a left or right delimiter
  lineNumber: int that represents the line where codeChar was located*/
void SyntaxAnalyzer::AddDelimiter(char codeChar, int delimiterCode, int lineNumber){

	if(delimiterCode == 0)
		delimiterData.left->Push(codeChar);	
	else if(delimiterCode == 1)
		delimiterData.right->Push(codeChar);
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
		//"bouncing "between two indexes 
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

/*ReverseDelimiterStack Methods
  Returns a pointer to a reversed char GenStack
  delimiterStack: char GenStack that is to be reversed, is pass by copy to allow the reversal occur without affecting the original stack object*/
GenStack<DelimiterData>* SyntaxAnalyzer::ReverseDelimiterStack(GenStack<DelimiterData> delimiterStack){
	
	GenStack<DelimiterData> *reversedDelimiterStack = new GenStack<DelimiterData>(delimiterStack.Size());
	
	while(!delimiterStack.Empty())	
		reversedDelimiterStack->Push(delimiterStack.Pop());

	return reversedDelimiterStack;
}

//---------------------------------------------------------------------------------

/*CoreLogic Function, has main core logic for determining if there is a delimiter syntax error
  Returns a bool representing whether or not there is a delimiter syntax error present in the code
  */
bool SyntaxAnalyzer::CoreLogic(char codeChar, int delimiterCode, int lineNumber){
	
	//for left side delimiters
	if(delimiterCode == 0){
		delimiterData.left->Push(codeChar);
		delimiterData.leftLineNumbers->Push(lineNumber);	
	}

	//for right side delimiters
	else if(delimiterCode == 1){
		
		if(delimiterData.left->Empty()){	
			cout << "Error, Line Number: " << lineNumber << ": '" << codeChar << "' found without starting delimiter." << endl;
			return false;
		}
		
		char leftDelimiter = delimiterData.left->Pop();
		if(codeChar != OppositeDelimiter(leftDelimiter)){
			cout << "Error, Line Number: " << lineNumber << ": Expecting ending delimiter for '" << leftDelimiter << "', but found '" << codeChar << "'" << endl;
			return false; 
		} 
	}

	return true;
}
