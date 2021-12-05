#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
#include "htmlChecker.h"

using namespace std;

int main()
{
    string fileName = "";
    cout << "Enter File Name: \n(Enter 'Quit' to quit)\n"; 
    cin >> fileName;
    while (fileName != "Quit"){
        htmlChecker html;
        if (html.readFile(fileName, "output.txt")) {
            html.checkFile("output.txt");
        }
        else {
            cout << "ERROR FILE NOT OPENED (readFile)\n";
        }
	cout << "Enter File Name: \n(Enter 'Quit' to quit)\n";
        cin >> fileName;
    }
    return 0;
}
