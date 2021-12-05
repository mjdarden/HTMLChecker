#include <iostream>
#include <fstream>
#include <string>
#include "htmlChecker.h"

htmlChecker::htmlChecker() 
{
    line = "";
    errors = false;
}

htmlChecker::~htmlChecker()
{
}

bool htmlChecker::readFile(string inputHTML, string outputHTML)
{
    ifstream din;
    din.open(inputHTML);
    if (din.fail()) return false;

    ofstream dout;
    dout.open(outputHTML);
    if (din.fail()) return false;

    char last = ' ';
    char ch = din.get();
    while (ch != EOF)
    {
        if (ch == '<' && last != '\n')
        {
            dout << endl;
            last = '\n';
        }
        if (ch != '\n')
        {
            dout << ch;
            last = ch;
        }
        if (ch == '>' && last != '\n')
        {
            dout << endl;
            last = '\n';
        }
        ch = din.get();
    }
    din.close();
    dout.close();
    return true;
}

void htmlChecker::checkFile(string fileName)
{
    ifstream file;
    file.open(fileName);
    if (!file.fail()) {
        while (getline(file, line)) {
            for (unsigned int i = 0; i < line.length(); i++) {
                line[i] = tolower(line[i]);
            }
            string temp = "";
            if (!line.empty()) {
                if ((line.front() == '<') && (line[1] != '/')) {
                    line.erase(line.begin());
                    for (unsigned int i = 0; i < line.length(); i++) {
                        if (line[i] == ' ') {
                            line.erase(i, line.length());
                            break;
                        }
                        else if (line[i] == '>') {
                            line.erase(line.end() - 1);
                        }
                    }
                    if ((line != ("br")) && (line != ("hr")) && (line != ("img"))) {
                        stack.Push(line);
                    }
                }
                if ((line.front() == '<') && (line[1] == '/')) {
                    line.erase(line.begin());
                    line.erase(line.begin());
                    for (unsigned int i = 0; i < line.length(); i++) {
                        if (line[i] == ' ') {
                            line.erase(i, line.length());
                            break;
                        }
                        else if (line[i] == '>') {
                            line.erase(line.end() - 1);
                        }
                    }
                    stack.Pop(temp);
                    if (line == temp) {
                        //cout << "MATCH!\n";
                    }
                    if ((line != temp) && (!stack.IsEmpty())) {
                        errors = true;
                        cout << "SYNTAX ERROR, Incorrect tag order, Open tag: <"
                            << temp << "> Close tag: </" << line << ">\n";
                    }
                    else if ((line != temp) && (stack.IsEmpty())) {
                        errors = true;
                        cout << "SYNTAX ERROR, No open tag for: </" << line << ">\n";
                    }
                }
            }
        }
        if (!stack.IsEmpty()) {
            errors = true;
            cout << "SYNTAX ERROR, Not all necessary tags closed.\n" <<
                "Missing closing tag(s) for:\n";
            string missing;
            while (!stack.IsEmpty()) {
                stack.Pop(missing);
                cout << '<' << missing << '>' << endl;
            }
        }
        if (!errors) {
            cout << "No errors found!\n";
        }
    }
    else {
        cout << "ERROR FILE NOT OPENED (checkFile)\n";
    }
    file.close();
}

