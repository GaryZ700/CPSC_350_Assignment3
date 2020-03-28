/*Identifiying Information:
	a. Gary Zeri
	b. Student ID: 2321569
	c. zeri@chapman.edu
	d. CPSC 350-02
	e. Assignment 3: Syntax Checker
*/

#ifndef GEN_STACK_H_
#define GEN_STACK_H_

#include <iostream>
#include "gen_stack_exceptions.h"

using namespace std;

/*Generic Stack Class*/
template <class T>
class GenStack{

	public:
		GenStack(int maxSize=20, int incrementSize=20);
		~GenStack();
		
		void Push(T obj);
		bool Empty();
		int Size();	
		T Pop();
		T Top();		
	private:
		void IncreaseSize();		

		int maxSize;
		int incrementSize;

		//if there is one element in the stack, then size will equal 1
		//if the stack size is full then the size will equal the max stack size 
		int size;

		T *data;	
};

/*Generic Stack Constructor*/
template <class T>
GenStack<T>::GenStack(int maxSize, int incrementSize){

	//check to ensure that the maxSize and incrementSize are valid 
	if(maxSize < 1)
		throw( new GenStackBadMaxSize() );
	else if(incrementSize < 1)
		throw( new GenStackBadIncrementSize );

	this->maxSize = maxSize;
	this->incrementSize = incrementSize;
	this->size = 0;
	this->data = new T[maxSize];
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Generic Stack Deconstructor*/
template <class T>
GenStack<T>::~GenStack(){
	delete[] data;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*GenStack Push Method
  Pushes the provided obj onto the Stack*/
template <class T>
void GenStack<T>::Push(T obj){

	//if the stack is alreadly full
	//then increase the size of the stack
	if(size == maxSize)
		IncreaseSize();

	data[size++] = obj;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Returns a bool specifying whether or not the Stack is Empty*/
template <class T>
bool GenStack<T>::Empty(){
	return (size == 0);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Returns the current size of the Stack*/
template <class T>
int GenStack<T>::Size(){
	return size;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Pop Method 
  Returns the top most obj in the stack, and also removes it from the stack
  Will throw an exception if the stack is empty*/
template <class T>
T GenStack<T>::Pop(){

	if(size == 0)
		throw( new GenStackEmptyPop() );

	return data[--size];
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/*Top Method
  Returns the top most object from the stack without removing it*/
template <class T>
T GenStack<T>::Top(){
	return data[size-1];
}

//---------------------------------------------------------------------------------

/*IncreaseSize Method
  Incrases the size of the Stack by teh incrementSize*/
template <class T>
void GenStack<T>::IncreaseSize(){

	maxSize += incrementSize;
	
	T *tempData = new T[maxSize];

	//transfer orginal data to the new larger data array
	for(int i=0; i<maxSize-incrementSize; ++i){
		tempData[i] = data[i];
	}

	delete[] data;
	data = tempData;
}

#endif //GEN_STACK_H_
