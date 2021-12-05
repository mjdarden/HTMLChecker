#pragma once
#include "Stack.h"

class htmlChecker
{
public:
	htmlChecker();
	~htmlChecker();

	bool readFile(string inputHTML, string outputHTML);
	void checkFile(string fileName);
private:
	string line;
	Stack stack;
	bool errors;
};


