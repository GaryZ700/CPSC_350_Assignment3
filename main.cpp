/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#include <fstream>
#include "menu.h"
#include "syntax_analyzer.h"
#include "assignment3_string_constants.h"

using namespace std;

int main(int argc, char** argv){

	bool correctDelimiterSyntax;
	bool firstRun = true;
	fstream codeFile;
	UserInput input;
	SyntaxAnalyzer syntaxAnalyzer;

	//if the user did not provide a command line argument 
	//prompt the user to input one
	if(argc == 1)
		codeFile = input.GetFile(kGetFileNoCmdlArg, kBadFileName, ios::in);	
	else
		codeFile = input.GetFile(argv[1], kBadFileName, kBadFileName, ios::in); 
		
	//do while loop that allows the user to repeat use of the program	
	do{
		//if the user would like to analyze another file
		//then prompt for another file name
		if(!firstRun)
			codeFile = input.GetFile(kGetFile, kBadFileName, ios::in);
		else
			firstRun = false;

		correctDelimiterSyntax = syntaxAnalyzer.Analyze(codeFile);
		codeFile.close();		
	}while(correctDelimiterSyntax && input.GetBool(kRepeatProgram, kYes, kNo));

	return 0;
}
