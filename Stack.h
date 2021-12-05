#pragma once
//-----------------------------------------------------------
//  Purpose:    Header file for the integer Stack class.
//  Author:     John Gauch
//-----------------------------------------------------------

#include <cmath>
#include <iostream>
#include <string>
using namespace std;

//-----------------------------------------------------------
// Stack data node definition
//-----------------------------------------------------------
struct StackNode
{
	string Number;
	StackNode* Next;
};

//-----------------------------------------------------------
// Define the Stack class interface 
//-----------------------------------------------------------
class Stack
{
public:
	// Constructors
	Stack();
	Stack(const Stack& stack);
	~Stack();

	// Methods
	bool IsFull();
	bool IsEmpty();
	void Push(string Number);
	void Pop(string& Number);
	void Top(string& Number);
	int GetLength();
	void Print();

private:
	StackNode* Head;
	int Length;
};


