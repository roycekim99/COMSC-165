#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>

using namespace std;

/***************************************************************
Problem: Theater Seating
Question: Write a program that can be used by a small theater to
sell tickets for performances.

Name: Royce Kim
ID: 1559541
Date: 09/30/2018
Status: complete
****************************************************************/

void clearTheater(vector<string> &chosen_vector) {
    chosen_vector.clear();
}

void display(vector<string>& vect, int seatSize) {
    string firstLine = "";
    string temp;
    stringstream ss;

    cout << endl;
    cout << setw(22) << right << "Seats" << endl;

    for (int i = 0; i < seatSize; i++) {
        ss << ( (i + 1)%10 ) << " ";
        ss >> temp;
        firstLine += temp;
    }
    cout << setw(seatSize + 8) << right << firstLine << endl;


    for (int i = 0; i < vect.size(); i++) {   //row count
        ss.clear();
        ss << i + 1;
        ss >> temp;
        temp = "row " + temp;
        cout << setw(7) << left << temp << " " << setw(seatSize) << right << vect.at(i) << endl;
    }

}

void load(const string &fileName, vector<string> &destinationVector, int &rowMax, int &seatsMax) {
    ifstream inputFile(fileName);
    string str;

    clearTheater(destinationVector);
    if (inputFile) {
        for (int count = 0; getline(inputFile, str); count++) {
            destinationVector.push_back(str);
        }
    }
    
    rowMax = destinationVector.size();
    seatsMax = destinationVector.at(0).size();

    cout << "Settings Imported." << endl;
    inputFile.close();
}

void save(const vector<string> &vectorInput, const string &fileName) {
    ofstream outputFile(fileName);

    if (outputFile) {
        for (string str : vectorInput) {
            outputFile << str << endl;
        }
    }

    cout << "Exported." << endl;
    outputFile.close();
}

vector<string> initializeTheater(int rowCount, int seats) {
    string row = "";

    for (int i = 0; i < seats; i++) {
        row += "#";
    }

    vector<string> theater(rowCount, row); //15 rows 
    save(theater, "setup.txt");
    return theater;
}

//1.purchase menu functions:

string findSeats(const vector<string> &originRows, int originSeats, int numberOfSeats, int startingRow = 0) { //find first possible seat
    string foundSeat = "none";
    string temp;
    string searchSeat = "";
    bool seatFound = false;
    int foundPos;
    stringstream ss;

    for (int i = 0; i < numberOfSeats; i++) { // generate searchable string
        searchSeat += "#";
    }

    for (int r = startingRow; r < originRows.size() && !seatFound; r++) { //find a row that it exists
        foundPos = originRows.at(r).find(searchSeat);
        if (foundPos < originSeats && foundPos >= 0) {
            foundSeat = "R";
            ss << (r + 1);
            ss >> temp;
            ss.clear();

            foundSeat += temp;
            ss << (originRows.at(r).find(searchSeat) + 1);
            ss >> temp;
            ss.clear();

            foundSeat += ("S" + temp);
            seatFound = true;
        }
    }

    return foundSeat;
}

bool seatIsThere(const vector<string> &originRows, int originSeats, int inRows, int inSeats) { //check if seat is available
    char seatChar;
    bool isAvailable = false;

    if ((inRows <= originRows.size()) || (inSeats <= originSeats)) {
        isAvailable = (originRows.at(inRows-1).at(inSeats-1) == '#');
    }
    return isAvailable;
}

void buySeat(vector<string> &seatings, int maxSeats, int &ticketsSold, const string &userInput, int numberOfSeats = 1) { //replace # with *
    int sPos = 0;
    int seatNum;
    int rowNum;
    stringstream ss;
    string seatChars = "";

    for (int i = 0; i < numberOfSeats; i++) {
        seatChars += "*";
    }

    sPos = userInput.find("S");
    ss << userInput.substr(1, sPos - 1); //find row
    ss >> rowNum;
    ss.clear();

    ss << userInput.substr(sPos + 1, userInput.size() - sPos);  //find seat
    ss >> seatNum;


    if (seatIsThere(seatings, maxSeats, rowNum, seatNum)) { //if seat is available
        seatings.at(rowNum - 1).replace(seatNum-1, seatChars.size(), seatChars);
        ticketsSold++;
        cout << "Seat Purchased!" << endl;
    }
    else { //if no seat found/taken
        cout << "No such seat or the seat has been taken." << endl << endl;
    }
} 

void purchaseMenu(vector<string> &theater, int seats, const string &fileName, int &ticketsSold) { //functions for the purchase menu
    int userCommand = 1;
    int numberOfSeats = 1;
    int rowStart;
    string userInput;
    string foundSeats;
    string searchSeat = "";

    while (userCommand != 0) {
        cout << endl << "*--<Purchase Menu>--*" << endl <<
            "1. Buy a seat" << endl <<
            "2. Find a seat" << endl <<
            "3. Display theater seats" << endl <<
            "0. Return to Main Menu" << endl;
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;

        switch (userCommand) {
        case 1: //buy a single seat
            cout << "Enter seat in R#S# format (ie. R10S25): ";
            getline(cin, userInput);

            buySeat(theater, seats, ticketsSold, userInput);
            save(theater, fileName);
            break;
        case 2: //find a seat
            cout << "How many seats would you like?";
            getline(cin, userInput);
            stringstream(userInput) >> numberOfSeats;

            cout << "From which row?";
            getline(cin, userInput);
            stringstream(userInput) >> rowStart;

            foundSeats = findSeats(theater, seats, numberOfSeats, rowStart - 1);

            if (!foundSeats.compare("none")) {  //if no seats were found
                cout << "No seats found" << endl << endl;
            }
            else {
                cout << "Seat is found at " << foundSeats << "." << endl <<
                    "Would you like to purchase it? [ Y(es) | N(o) ] " << endl;
                getline(cin, userInput);

                if (toupper(userInput.at(0)) == 'Y') {
                    buySeat(theater, seats, ticketsSold, foundSeats, numberOfSeats);
                    save(theater, fileName);
                }
                
            }
            
            break;
        case 3:
            display(theater, seats);
            break;
        case 0: //return to main menu
            break;//avoid default prompt
        default:
            cout << "Unknown command, please try again" << endl << endl;
            break;
        }
    }
}

int main() {
    //initial 
    const string FILENAME("setup.txt");

    string userInput;
    int seatsMax = 30;
    int rowsMax = 15;
    int ticketsSold = 0;
    int userCommand = 1;
    vector<string> theater;
    ifstream fileInput(FILENAME);
    //--------

    cout << "Movie Seating Application" << endl;

    if (fileInput) {//on success
        load(FILENAME, theater, rowsMax, seatsMax);  // import at first
    }
    else {//else: initialize
       theater = initializeTheater(rowsMax, seatsMax);
    }

    display(theater, seatsMax);
    cout << endl;
    
    while (userCommand != 0) {
        cout << "---<Main Menu>---" << endl <<
                "1. Purchase Tickets" << endl <<
                "2. Settings" << endl <<
                "3. Display theater seats" << endl <<
                "4. Check number of tickets sold"
                "0. Exit" << endl;
         
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;

        switch (userCommand) {
        case 1:
            purchaseMenu(theater,seatsMax,FILENAME, ticketsSold);
            userCommand = 1;
            break;
        case 2:
            break;
        case 3:
            display(theater, seatsMax);
            cout << endl;
            break;
        case 0://avoid default prompt
            break;
        default:
            cout << "Unknown command, please try again" << endl << endl;
            break;
        }
    }// end while


    /**TODO 1: user can set up:
               Number of rows
               Number of seats per row
               Default seat price
               List of special row prices (1.2)
               List of blocked seats listed entered in one line
     **/

     //TODO 3: view number of tickets sold
     //TODO 3.1: user buys a ticket of a group of tickets
     //TODO 3.2: ----display total ticket prices

     //TODO 4: keep track of all total ticket sales
     //TODO 4.1: #seats sold, #available seats in each row, and # of available seats in theater

     //TODO 5.1: x-number of adjacent seats, the program will auto-find the seats
     //TODO 5.2: ----AT A GIVEN ROW and find a row with the seats (going back)

     //TODO 6: clear all sales

     //TODO 7: exit option. must save at close and load at start
    return 0;
}