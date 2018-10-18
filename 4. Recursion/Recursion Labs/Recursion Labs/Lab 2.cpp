#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/***************************************************************
Problem: Recursive lab 2
Question: Write a recursive function that displays a string
reversely on the console.
Name: Royce Kim
ID: 1559541
Date: 10/11/2018
Status: complete
****************************************************************/

void reverseDisplay(const string& s) {
    cout << s.at(s.size() - 1);
    if (s.size() > 1) {
        reverseDisplay(s.substr(0, s.size() - 1));
    }
}

int main() {
    string userInput;
    char repeatChar = ' ';

    cout << "Input a string to reverse ==| ";
    getline(cin, userInput);
    reverseDisplay(userInput);

    return 0;
}