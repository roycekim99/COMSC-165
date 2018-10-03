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

int countTix(const vector<string> &theater) {
    int tix = 0;
    for (string row : theater) {
        for (char seat : row) {
            tix += seat == '*';
        }
    }
    return tix;
}

void display(vector<string>& vect, int seatSize) {
    string firstLine = "";
    string temp;
    stringstream ss;

    cout << endl;
    cout << setw(22) << right << "Seats" << endl;

   // cout << seatSize << "=seatsize" << endl;    //DEBUG
    for (int i = 0; i < seatSize; i++) {
        ss << ( (i + 1)%10 ) << " ";
        ss >> temp;
        firstLine += temp;
    }
    cout << setw(seatSize + 8) << right << firstLine << endl;

   // cout << vect.size() << "=vect size" << endl;  //DEBUG
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

bool strIsNum(const string &checkStr) { //check if input is number
   return checkStr.find_first_not_of("0123456789") == string::npos;
}

void buySeat(vector<string> &seatings, int maxSeats, int &ticketsSold, const string &userInput, int numberOfSeats = 1) { //replace # with *
    int sPos = userInput.find("S");
    int seatNum;
    int rowNum;
    stringstream ss;
    string seatChars = "";
    string seatString = userInput.substr(sPos + 1, userInput.size() - sPos);
    string rowString = userInput.substr(1, sPos - 1);

    for (int i = 0; i < numberOfSeats; i++) {
        seatChars += "*";
    }

    //split input into R, rowNum, S, seatNum
    if (userInput.at(0) == 'R' && sPos &&
        (strIsNum(rowString) && strIsNum(seatString)) ) {

        ss << rowString; //find row
        ss >> rowNum;   //
        ss.clear();

        ss << seatString;  //find seat
        ss >> seatNum;  //

        if (seatIsThere(seatings, maxSeats, rowNum, seatNum)) { //if seat is available
            seatings.at(rowNum - 1).replace(seatNum - 1, seatChars.size(), seatChars);
            ticketsSold++;
            cout << "Seat Purchased!" << endl;
        }
    }
    else { //if no seat found/taken
        cout << "No such seat or the seat has been taken." << endl << endl;
    }
} 

void purchaseMenu(vector<string> &theater, int seats, const string &fileName, int &ticketsSold) { //functions for the purchase menu
    int userCommand = 1;
    int numberOfSeats = 1;
    int rowStart;
    double ticketPrice = 11.50;
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
                    "Would you like to purchase it? [ Y(es) | N(o) ] ";
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

//Setup menu

vector<string> scaleTheater(const vector<string> &initialTheater, int currentSeatMax, int newRowMax, int newSeatMax) {
    vector<string> newTheater;
    int size;
    newTheater = initializeTheater(newRowMax, newSeatMax); //fill with '*'
    display(newTheater, newSeatMax);    //DEBUG

    size = (initialTheater.size() < newRowMax) ? initialTheater.size() : newRowMax;

    for (int i = 0; i < size; i++) { //replace with original inputs
        cout << newTheater.at(i) << endl;   //DEBUG
        
        newTheater.at(i).replace(0, newSeatMax, initialTheater.at(i)); 
        cout << newTheater.at(i) << endl;   //DEBUG
    }
    return newTheater;
}

void initializeSeatPrices(vector<int> &seatPrices, int price ) {
    for (int seatPrice : seatPrices) {
        seatPrice = price;
    }
}

void setupMenu(vector<string> &theater, int &currentMaxRows, int &currentMaxSeats, vector<int> &rowPrices) {
    string userInput;
    vector<string> originalTheater = theater;
    int userCommand = 1;
    int requested;
    int delta = 0;
    int newRowMax = currentMaxRows;
    int newSeatmax = currentMaxSeats;
    /**
    numeber of rows
    number of seats per row
    default seat price
    list of special row prices
        R, num, $, #
    list of blocked seats
        R15S10 R7S10 R2S3... separated by spaces (getline using space delemeter)
    **/
    while (userCommand != 0) {
        cout << endl << "}}--Set Up Menu--{{" << endl <<
            "1. Set up Wizard" << endl <<
            "2. Change # of rows" << endl <<
            "3. Change # of seats per row" << endl <<
            "4. Add special row prices" << endl <<
            "5. Add blocked seats" << endl <<
            "0. Return to Main Menu..." << endl;
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;

        switch (userCommand) {
        case 1:
            break;
        case 2:
        case 3:
            cout << "The current max amount of " << ((userCommand == 2) ? "rows" : "seats") << " is " << ((userCommand == 2) ? currentMaxRows : currentMaxSeats) << "." << endl;
            cout << "What would you like to change it to?";
            getline(cin, userInput);
            stringstream(userInput) >> requested;

            (userCommand == 2) ? newRowMax = requested : newSeatmax = requested;

            theater = scaleTheater(theater, currentMaxSeats, newRowMax, newSeatmax);
            currentMaxRows = newRowMax;
            currentMaxSeats = newSeatmax;

            display(theater, currentMaxSeats);
            break;
        case 4:

            break;
        case 5:
            break;

        case 0:
            cout << "Would you like to save your changes? Yes|No :";
            getline(cin, userInput);

            if (toupper(userInput.at(0)) == 'Y') {
                //TODO: SAVE
            }
            else {
                theater = originalTheater;  //IMPROVE
            }

            break;
        default:
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
    vector<int> rowPrices;
    ifstream fileInput(FILENAME);
    //--------

    cout << "Movie Seating Application" << endl;

    if (fileInput) {//on success
        load(FILENAME, theater, rowsMax, seatsMax);  // import at first
    }
    else {//else: initialize
        theater = initializeTheater(rowsMax, seatsMax);
        save(theater, "setup.txt");
    }

    display(theater, seatsMax);
    cout << endl;
    
    while (userCommand != 0) {
        ticketsSold = countTix(theater);
        cout << "Total Tickets Sold: " << ticketsSold << endl;
        cout << "---<Main Menu>---" << endl <<
                "1. Purchase Tickets" << endl <<
                "2. Set Up" << endl <<
                "3. Display theater seats" << endl <<
                "4. Check number of tickets sold" << endl <<
                "0. Exit" << endl;
         
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;

        switch (userCommand) {
        case 1:
            purchaseMenu(theater,seatsMax,FILENAME, ticketsSold);
            userCommand = 1;
            break;
        case 2:
            //TODO: Settings menu (by wednesday)
            setupMenu(theater,rowsMax,seatsMax, rowPrices);
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

    return 0;
}
