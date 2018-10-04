#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <thread> 
#include <chrono> 

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

void replaceSeats(string &newSeats, const string &initialSeats) {
    int lowerSeatMax = ((newSeats.size() < initialSeats.size() )? newSeats.size() : initialSeats.size());
    for (int i = 0; i < lowerSeatMax; i++) {
        newSeats.at(i) = initialSeats.at(i);
    }
    
}

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
    for (int i = 0; i < seatSize; i++) {    //display seats
        ss << ((i + 1) % 10);
        ss >> temp;
        firstLine += temp;
        ss.clear();
    }
    cout << setw(seatSize + 8) << right << firstLine << endl;

   // cout << vect.size() << "=vect size" << endl;  //DEBUG
    for (int i = 0; i < vect.size(); i++) {   //row count
        ss << (i + 1);
        ss >> temp;
        temp = "row " + temp;
        cout << setw(7) << left << temp << " " << setw(seatSize) << left << vect.at(i) << endl;
        ss.clear();
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
    stringstream ss;
    bool seatFound = false;
    int foundPos;

    for (int i = 0; i < numberOfSeats; i++) { // generate searchable string
        searchSeat += "#";
    }

    for (int r = startingRow; r < originRows.size() && !seatFound; r++) { //find a row that it exists
        foundPos = originRows.at(r).find(searchSeat);

        if (foundPos < originSeats && foundPos >= 0) {
            foundSeat = "R";
            ss << (r + 1);
            ss >> temp;

            foundSeat += temp;
            ss.clear();

            ss << (foundPos + 1);
            ss >> temp;

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
   return checkStr.find_first_not_of(".0123456789") == string::npos;
}

void buySeat(vector<string> &inputVector, int maxSeats, const string &userInput, int numberOfSeats = 1) { //replace # with *
    int sPos = userInput.find("S");
    int seatNum;
    int rowNum;
    string seatChars = "";
    string seatString = userInput.substr(sPos + 1, userInput.size() - sPos);
    string rowString = userInput.substr(1, sPos - 1);

    for (int i = 0; i < numberOfSeats; i++) {
        seatChars += "*";
    }

    //split input into R, rowNum, S, seatNum
    if (userInput.at(0) == 'R' && sPos &&
        (strIsNum(rowString) && strIsNum(seatString)) ) {

        stringstream(rowString) >> rowNum; //find row

        stringstream(seatString) >> seatNum;  //find seat

        if (seatIsThere(inputVector, maxSeats, rowNum, seatNum)) { //if seat is available
            inputVector.at(rowNum - 1).replace(seatNum - 1, seatChars.size(), seatChars);
            cout << "Seat Purchased!" << endl;
        }
    }
    else { //if no seat found/taken
        cout << "No such seat or the seat has been taken." << endl << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
} 

void purchaseMenu(vector<string> &theater, int maxSeats, const string &fileName, int &ticketsSold) { //functions for the purchase menu
    int userCommand = 1;
    int requestedSeats = 1;
    int rowStart;
    double ticketPrice = 11.50;
    string userInput;
    string foundSeats;
    string searchSeat = "";

    while (userCommand != 0) {
        system("cls");
        display(theater, maxSeats);

        cout << endl << "*--<Purchase Menu>--*" << endl <<
            "1. Buy a seat" << endl <<
            "2. Find a seat" << endl <<
            "0. Return to Main Menu" << endl;
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;

        switch (userCommand) {
        case 1: //buy a single seat
            system("cls");
            display(theater, maxSeats);

            cout << "Enter seat in R#S# format (ie. R10S25): ";
            getline(cin, userInput);
            buySeat(theater, maxSeats, userInput);
            save(theater, fileName);
            break;
        case 2: //find a seat
            system("cls");
            display(theater, maxSeats);

            cout << "How many seats would you like?";
            getline(cin, userInput);
            stringstream(userInput) >> requestedSeats;

            cout << "From which row?";
            getline(cin, userInput);
            stringstream(userInput) >> rowStart;

            foundSeats = findSeats(theater, maxSeats, requestedSeats, rowStart - 1);

            if (!foundSeats.compare("none")) {  //if no seats were found

                cout << "No seats found" << endl << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
            else {
                cout << "Seat is found at " << foundSeats << "." << endl <<
                    "Would you like to purchase it? [ Y(es) | N(o) ] ";
                getline(cin, userInput);

                if (toupper(userInput.at(0)) == 'Y') {
                    buySeat(theater, maxSeats, foundSeats, requestedSeats);
                    save(theater, fileName);
                }
                
            }
            break;
        case 0: //return to main menu
            break;//avoid default prompt
        default:
            cout << "Unknown command, please try again" << endl << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        }
    }
}

//Setup menu

vector<string> scaleTheater(const vector<string> &initialTheater, int currentSeatMax, int newRowMax, int newSeatMax) {
    vector<string> newTheater;
    int size;
    newTheater = initializeTheater(newRowMax, newSeatMax); //fill with '*'

    size = (initialTheater.size() < newRowMax) ? initialTheater.size() : newRowMax;

    for (int i = 0; i < size; i++) { //replace with original inputs
         replaceSeats(newTheater.at(i), initialTheater.at(i));

    }

    return newTheater;
}

void initializeSeatPrices(vector<string> &seatPrices, double price,int maxRows, bool saveOld ) {
    int rowPos = 0;
    int sPos;
    double priceNum;

    string priceString = "";
    stringstream ss;
    ss << price;
    ss >> priceString;

    vector<string> tempPrices(maxRows, priceString);

    if (saveOld) {
        for (int i = 0; i < maxRows; i++) {
            sPos = seatPrices.at(i).find("*");
            if (sPos) {
                priceString = seatPrices.at(i).substr(1, seatPrices.at(i).size() - 2);
                
            }
            sPos = 0;
         }
    }
    seatPrices = tempPrices;   //sets maximum number of prices

}

string specialSeatPrices(vector<string> &rowPrices, const string &userInput, int maxRows ) {
    int sPos;
    int rowNum;
    double price;
    string token;
    string rowString;
    string priceString;
    string invalidStrings = "";
    stringstream ss(userInput);

    while (getline(ss, token, ' ')) {
        sPos = token.find("$");

        if (toupper(token.at(0)) == 'R' && sPos) {//start validation

            rowString = userInput.substr(1, sPos - 1);
            priceString = userInput.substr(sPos + 1, userInput.size() - sPos);

            stringstream(rowString) >> rowNum;
                
            if (((rowNum - 1) < maxRows) && (strIsNum(priceString)) ) {
                stringstream(priceString) >> price; //finish validation
                rowPrices.at((rowNum - 1)) = price;
            }
            else {
                invalidStrings += (token + "\n");
            }
        }
        else {
            invalidStrings += (token + "\n");
        }
    }
    return invalidStrings;
}

void setupMenu(vector<string> &theater, int &currentMaxRows, int &currentMaxSeats, vector<string> &rowPrices) {
    string userInput;
    string invalidStrings = "";
    vector<string> originalTheater = theater;
    bool replaceCurrent = true;
    int originalMaxSeats = currentMaxSeats;
    int userCommand = 1;
    int requested;
    int delta = 0;
    int newRowMax = currentMaxRows;
    int newSeatmax = currentMaxSeats;
    double userDefaultPrice = 0.0;
    
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
        system("cls");
        display(theater, currentMaxSeats);

        cout << endl << "}}--Set Up Menu--{{" << endl <<
            "1. Set up Wizard" << endl <<
            "2. Change # of rows" << endl <<
            "3. Change # of seats per row" << endl <<
            "4. Change Row Prices" << endl <<
            "5. Add blocked seats" << endl <<
            "0. Return to Main Menu..." << endl;
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;
 
        switch (userCommand) {
        case 1:
            cout << "*****<Setup Wizard>*****" << endl;
            //TODO
            break;
        case 2:
        case 3:
            system("cls");
            display(theater, currentMaxSeats);

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
            system("cls");
            display(theater, currentMaxSeats);
            
            cout << "Please enter all row's default price: $";
            getline(cin, userInput);
            if (strIsNum(userInput)) {
                stringstream(userInput) >> userDefaultPrice;

                initializeSeatPrices(rowPrices, userDefaultPrice, theater.size(),false);
                cout << "Replace current costs? Yes | No >>";
                getline(cin, userInput);
                replaceCurrent = ( (toupper(userInput.at(0)) == 'Y') );

                

                cout << "All seats now cost $" << userDefaultPrice << endl;  //if replace ok
                cout << "Would you like to add special row prices? Yes | No >>";
                getline(cin, userInput);
                if (toupper(userInput.at(0)) == 'Y') {

                    cout << "Enter a list of special rows and prices in R#$# format (You may input multiple, spaces between each input)" << endl <<
                        "ex: (R10$20 R2$21 R30$2)";
                    getline(cin, userInput);
                    
                    invalidStrings = specialSeatPrices(rowPrices, userInput, currentMaxRows);
                    cout << (!(invalidStrings.compare("")) ? "Some inputs were invalid:" : "") << endl << ( (!invalidStrings.compare("") ? invalidStrings : "") );
                }
            }
            else {
                cout << "Input invalid." << endl;
            }
            

            break;
        case 5:
            break;

        case 0:
            system("cls");
            display(theater, currentMaxSeats);

            cout << "Would you like to save your changes? Yes|No :";
            getline(cin, userInput);

            if (toupper(userInput.at(0)) == 'Y') {
                //TODO: SAVE
                save(theater, "setup.txt");
            }
            else {
                currentMaxSeats = originalMaxSeats;
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
    vector<string> rowPrices;   //string as it contains specialrows and price
    ifstream fileInput(FILENAME);
    //--------

    if (fileInput) {//on success
        load(FILENAME, theater, rowsMax, seatsMax);  // import at first
    }
    else {//else: initialize
        theater = initializeTheater(rowsMax, seatsMax);
        save(theater, "setup.txt");
    }
    cout << endl;
    
    while (userCommand != 0) {
        system("cls");
        display(theater, seatsMax);

        cout << endl;
        ticketsSold = countTix(theater);
        cout << "Total Tickets Sold: " << ticketsSold << endl;
        cout << "---<Main Menu>---" << endl <<
                "1. Purchase Tickets" << endl <<
                "2. Set Up" << endl <<
                "0. Exit" << endl;
         
        getline(cin, userInput);
        stringstream(userInput) >> userCommand;

        switch (userCommand) {
        case 1:
            system("cls");
            purchaseMenu(theater,seatsMax,FILENAME, ticketsSold);
            userCommand = 1;
            break;
        case 2:
            system("cls");
            //TODO: Settings menu (by wednesday)
            setupMenu(theater,rowsMax,seatsMax, rowPrices);
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
