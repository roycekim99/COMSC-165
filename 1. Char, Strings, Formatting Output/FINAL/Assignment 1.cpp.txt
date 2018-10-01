#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <bitset>
using namespace std;

/***************************************************************
Problem: Assignment 1
Question: Write a program that asks the user for his/her name. The program will
ask the user to enter 3 character values: a letter, a number, and a
symbol (such as: B, 6, and #). 

Name: Royce Kim
ID: 1559541
Date: 06/19/2018
Status: complete
****************************************************************/

int main() {		//Main
	char charInput = ' ';
	char sym = ' ';
	int numb = -1;
	string name;
	string userInput;

	cout << "What is your name? : ";	//getName
	getline(cin, name);
	
	cout << endl << "OK " << name << ", please input a letter, number, and a symbol separated by a space: ";
	getline(cin, userInput);
	stringstream(userInput) >> charInput >> numb >> sym;
	cout << endl;

	//formated output
	cout << name << " - Character Formatting" << endl;

	cout << endl << "\tletter = " << charInput <<
			"\tnumber = " << numb <<
			"\tsymbol = " << sym << endl;

	cout << "_____________________________________________________________________________" << endl;	//77

	cout << setw(10) << left << "Decimal" << setfill(' ') << //outputs DECI output 
			right << setw(5) << static_cast<int>(charInput) << 
			setw(15) << numb << 
			setw(15) << static_cast<int>(sym) << endl;
 
	cout << setw(10) << left << "Hex" << uppercase << setbase(16) << right << showbase << //output HEXADECIMAL output
			setw(5) << static_cast<int>(charInput) << 
			setw(15) << numb <<
			setw(15) << static_cast<int>(sym) << endl;

	cout << setw(10) << left << "Octal" << setbase(8) << //Output OCTAL output
			right << setw(5)  << static_cast<int>(charInput) << 
			setw(15) << numb << 
			setw(15) << static_cast<int>(sym) << endl;

	cout << setw(10) << left << "Binary" << //Output BINARY output
			right << setw(5) << bitset<8>(static_cast<int>(charInput)) << 
			setw(15) << bitset<8>(numb) << 
			setw(15) << bitset<8>(static_cast<int>(sym)) << endl;

	return 0;
}