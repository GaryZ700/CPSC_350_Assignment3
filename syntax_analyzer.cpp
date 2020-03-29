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
		
		cout << codeChar << " ";

		//check that a set of left and right delimiters have been acquired before executing the core logic
		//and if there are any syntax problems then return false
		if(delimiterData.right->Size() > 0)
			if(delimiterCode == 1)
				if(delimiterData.left->Size() > 0){
					if(CoreLogic(codeChar, delimiterCode, lineNumber) == false)
						return false;
				}
				else{
					cout << delimiterData.left->Size() << endl;
					cout << "Error, Line Number: " << lineNumber << ": '" << codeChar << "' missing starting delimiter." << endl;		
					return false;
				}
			
		AddDelimiter(codeChar, delimiterCode);	
	}

	//check if there were no ending delimiters
	if(delimiterData.left->Size() > 0 && delimiterData.right->Size() == 0){
		cout << "Error, End of File Reached: '" << codeChar << "' missing ending delimiter." << endl;
		return false;
	}
	
	//run core logic again to check the last set of delimiters to ensure that they are correct	
	return CoreLogic(codeChar, delimiterCode, lineNumber);
}

//---------------------------------------------------------------------------------

/*AddDelmiter Method
  Has a void return
  codeChar: char representing the character to add as a delimiter
  delimiterCode: int representing whether the delimiter is either a left or right delimiter*/
void SyntaxAnalyzer::AddDelimiter(char codeChar, int delimiterCode){

	if(delimiterCode == 0)
		delimiterData.left->Push(codeChar);	
	else if(delimiterCode == 1)
		delimiterData.right->Push(codeChar);
}

//---------------------------------------------------------------------------------

/*IsDelimiter Method
  Returns an int representing whether the specified char is an invalid delmiter, or a left or right side delmiter
	-1 = Invalid Delimiter 
	 1 = Right Side Delimiter
	 0 = Left Side Delimiter
  codeChar: char that is to be tested to determine if it is a delimiter*/
int SyntaxAnalyzer::IsDelimiter(char codeChar){

	int index = 2;
	int lastIndex = -1;

	//perform a binary search on the delimiters string in order to check if the test char is a valid delmiter
	while(index >= 0 && index <= 5 && lastIndex != index){

//		cout << "!!!!!!!!!!" << endl;
		//get last index every other cycle to check if 
		//there is an inbetween value that results in
		//"bouncing "between two indexes 
		if(index %2 == 0)
			lastIndex = index;

		if(codeChar == delimiters[index]){
			return index % 2;
		}
		else if(codeChar > delimiters[index])
			++index;
		else 
			--index;

//		cout << " " << delimiters[index] << " ";
	}

	return -1;
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
	cout << endl << "Core Logic Line Number!!!!!!!: " << lineNumber << endl;
	cout << codeChar << endl; 
	return true;
}
