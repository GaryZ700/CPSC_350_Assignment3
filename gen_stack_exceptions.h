/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#ifndef GEN_STACK_EXCEPTION_H_
#define GEN_STACK_EXCEPTION_H_

#include <exception>
#include <string>

using namespace std;

struct GenStackBadMaxSize : exception{
	const char  *what() const throw(){
		return "Stack max size must be greater than or equal to 1.";
	}
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct GenStackBadIncrementSize : exception{
	const char  *what() const throw(){
		return "Stack increment size must be greater than or equal to 1.";
	}
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct GenStackEmptyPop : exception{
	const char  *what() const throw(){
		return "Can not pop an empty stack.";
	}
};

#endif //GEN_STACK_EXCEPTION_H_
