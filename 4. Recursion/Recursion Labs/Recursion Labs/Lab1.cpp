#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/***************************************************************
Problem: Recursive lab 1
Question: Write a recursive function that finds the number of
occurences of a specified letter in a string.
Name: Royce Kim
ID: 1559541
Date: 10/11/2018
Status: complete
****************************************************************/

int count(const string& s, char a) {
    return (toupper( s.at(s.size()-1) ) == toupper(a)) +
        ( (s.size() > 1)? count(s.substr(0,s.size()-1), a) : 0);
}

int main() {
    string userInput;
    char repeatChar = ' ';

    cout << "Input a string and a char, it will "<<
        "repeat the last char of your input. ==| ";
    getline(cin, userInput);


    repeatChar = userInput.at(userInput.size()-1);
    cout << "we get " << 
        count(userInput.substr(0,userInput.size()-2), repeatChar) <<
        " repeats.";
   
    return 0;
}