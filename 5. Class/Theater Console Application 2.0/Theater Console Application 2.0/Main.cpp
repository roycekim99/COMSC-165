#include "Theater.h"
#include <Windows.h>
#include <thread>
#include <chrono>

/***************************************************************
Problem: Movie Theater 2.0
Question: Write a program that can be used by a small theater OR 
customers
Name: Royce Kim
ID: 1559541
Date: 10/18/2018
Status: incomplete
****************************************************************/

const string DEFAULT_FILENAME = "test.txt";
const string BLOCKED = "\033[0;31m";
const string AVAILABLE = "\033[1;32m";
const string TAKEN = "\033[0;33m";
const string SPECIAL = "\033[0;35m";
const string NEUTRAL = "\033[0m";

//::check if input is number
bool strIsNum(const string &checkStr) { 
    return checkStr.find_first_not_of(".0123456789") == string::npos;
}

//::display theater
void displayTheater(Theater theater) {
    stringstream ss;
    string buffer;
    string row;
    ss << theater;

   
    cout << "\033[1;36m<==" << theater.getName() << "==>\033[0m" << endl;
    
    cout << setw((theater.getRow(1).size() / 2) + 10) << right << "Seats" << endl;
    cout << setw(8);

    for (int i = 1; i <= theater.getSeatMaxAtRow(1); ++i) {
        cout << (i%10);
    }
    cout << endl;

    //TODO: change text color based on status
    for(int i = 1; ss >> buffer; ++i) {
        cout << NEUTRAL;
        cout << "Row " << setw(3) << left << i;//Row ##
        row = theater.getRow(i).info();
        for (char status : row) {
            switch (status) {
            case (static_cast<char>(Status::AVAILABLE)):
                cout << AVAILABLE;
                break;
            case (static_cast<char>(Status::TAKEN)):
                cout << TAKEN;
                break;
            case (static_cast<char>(Status::BLOCKED)):
                cout << BLOCKED;
                break;
            default:
                break;
            }
            cout << status;
        }
        cout << NEUTRAL;
        cout << "-$" << theater.getPrice(i) << endl;
    }
    cout << NEUTRAL;
}

int main() {
    string userInput;
    char choice = 'Y';
    double priceThisRun = 0.0;
    fstream fileStream(DEFAULT_FILENAME,ios::out | ios::in);
    Theater theater(DEFAULT_FILENAME);
    POINT p;


    if (fileStream) {
        cout << "File load success." << endl;
        theater.load(DEFAULT_FILENAME);
    }
    else {
        cout << "Could not open file. Using default settings." << endl;

    }

    this_thread::sleep_for(chrono::seconds(1));
    system("cls");
    cout << "Will you be purchasing a ticket? Y|N: ";
    getline(cin, userInput);
    stringstream(userInput) >> choice;
    
    switch ( toupper(choice) ) {
    //customer
    case 'Y':
        system("cls");
        displayTheater(theater);



        break;
    //admin (Jank)
    case 'N':
        //"loading"
        system("cls");
        cout << "I hope you're an admin.";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        this_thread::sleep_for(chrono::seconds(1));
        cout << ".";
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
        //end "loading"





    default:
        break;
    }

    return 1;
}