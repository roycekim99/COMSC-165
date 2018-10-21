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

//::set list to special row prices
void setSpeicalRows(Theater &theater, stringstream& ss) {
    string buffer;
    string price;
    int rowNum = 0;
    char dummy = ' ';
    stringstream splitStream;

    while (ss >> buffer) {
        splitStream << buffer;
        splitStream >> dummy >> rowNum >> dummy >> price;
        theater.setPrice(rowNum, price, true);
        splitStream.clear();
    }
}

//::set list to blocked rows
void setBlockedRows(Theater &theater, stringstream& ss) {
    string buffer;
    int seatNum = 0;
    int rowNum = 0;
    char dummy = ' ';
    stringstream splitStream;

    while (ss >> buffer) {
        splitStream << buffer;
        splitStream >> dummy >> rowNum >> dummy >> seatNum;
        theater.updateSeat(rowNum, seatNum, Status::BLOCKED);
        splitStream.clear();
    }
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

//::display prices only
void displayPrices(Theater theater) {
    for (int i = 1; i <= theater.size(); ++i) {
        cout << "Row " << i << ": ";
        if (theater.getRow(i).isSpecial()) {
            cout << SPECIAL << "$" << theater.getPrice(i) << NEUTRAL << endl;
        }
        else {
            cout << "$" << theater.getPrice(i) << endl;
        }
    }
}

//TODO::setup theater

int main() {
    bool success = false;
    string userInput;
    string foundSeat;
    char choice = 'Y';
    double priceThisRun = 0.0;
    double priceOfRow = 0.0;
    int userCommand = 1;
    int requestedSeats = 0;
    int rowStart = 0;
    int seatStart = 0;
    stringstream ss;
    fstream fileStream(DEFAULT_FILENAME, ios::out | ios::in);
    Theater theater(DEFAULT_FILENAME);
    Theater temp = theater;

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

    switch (toupper(choice)) {
        //customer
    case 'Y':
        //menu
        while (userCommand) {
            system("cls");
            displayTheater(theater);

            cout << "Your Total: " << priceThisRun << endl;
            cout << SPECIAL << "---<Main Menu>---" << NEUTRAL << endl;
            cout << "1.Find a seat" << endl <<
                "2. Purchase a seat" << endl <<
                "0. Exit" << endl;
            cout << "==| ";

            getline(cin, userInput);
            stringstream(userInput) >> userCommand;
            switch (userCommand) {
                //find a seat
            case 1:
                system("cls");
                cout << "How many seats would you like?";
                getline(cin, userInput);

                if (strIsNum(userInput)) {
                    stringstream(userInput) >> requestedSeats;

                    cout << "From which row?";
                    getline(cin, userInput);

                    if (strIsNum(userInput)) {
                        stringstream(userInput) >> rowStart;

                        foundSeat = theater.findSeats(requestedSeats, rowStart);

                        if (!foundSeat.compare("Not Found")) {

                            cout << "No seats found" << endl << endl;
                            this_thread::sleep_for(chrono::seconds(2));
                        }
                        else {

                            cout << "Found a seat at " << foundSeat << "." << endl;
                            cout << "Would you like to buy it? [Yes | No]";
                            getline(cin, userInput);

                            if (toupper(userInput.at(0)) == 'Y') {
                                stringstream(foundSeat) >> choice >> rowStart >> choice >> seatStart;
                                stringstream(theater.getPrice(rowStart)) >> priceOfRow;

                                for (int i = seatStart; i < requestedSeats + seatStart; ++i) {
                                    theater.updateSeat(rowStart, i, Status::TAKEN);
                                    //update current price
                                    priceThisRun += priceOfRow;
                                }

                            }

                        }//!foundSeat.compare("Not Found")


                    }//strIsNum(userInput)
                    else {
                        cout << "Unkown Input." << endl;
                        this_thread::sleep_for(chrono::seconds(1));
                    }
                }//strIsNum(userInput)
                else {
                    cout << "Unkown Input." << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                }


                break;
                //purchase a seat
            case 2:
                system("cls");
                displayTheater(theater);

                cout << "Enter seat in R#S# format (ie. R10S25): ";
                getline(cin, userInput);
                stringstream(userInput) >> choice >> rowStart >> choice >> seatStart;

                success = theater.updateSeat(rowStart, seatStart, Status::TAKEN);

                if (success) {
                    cout << AVAILABLE << "Purchas Successful!" << NEUTRAL << endl;
                    stringstream(theater.getPrice(rowStart)) >> priceOfRow;
                    priceThisRun += priceOfRow;//update current price 
                    this_thread::sleep_for(chrono::seconds(1));
                }
                else {
                    cout << TAKEN << "Purchas Failed" << NEUTRAL;
                    this_thread::sleep_for(chrono::seconds(1));
                }

                break;
            case 0: //don't say anything
                break;
            default:
                system("cls");
                cout << "Unkown input. Please try again." << endl;
                break;
            }
        }

        break;//case 'y'
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

        //menu
        while (userCommand != 0) {
            displayTheater(theater);
            cout << "Current Total Sales:" << SPECIAL << "$" <<
                theater.calculateTotalPrice() << NEUTRAL << endl;
            cout << endl << SPECIAL << "}}--Set Up Menu--{{" << endl << NEUTRAL <<
                "1. Set up Wizard (Start a new Theater)" << endl <<
                "2. Change # of rows" << endl <<
                "3. Change # of seats per row" << endl <<
                "4. Change Row Prices" << endl <<
                "5. Add blocked seats" << endl <<
                "6. Clear current Theater" << endl <<
                "0. Exit..." << endl;
            getline(cin, userInput);
            stringstream(userInput) >> userCommand;

            switch (userCommand) {
            case 1:
                //setupWizard(theater);
                break;
            case 2:
            case 3:
                system("cls");
                displayTheater(theater);

                cout << "WARNING: smaller sizes could delete" <<
                    "special row prices!!!" << endl;//warning text

                cout << "The current max amount of " <<
                    ((userCommand == 2) ? "rows" : "seats") <<
                    " is " <<
                    ((userCommand == 2) ?
                     theater.size() : theater.getSeatMaxAtRow(1)) <<
                    "." << endl;

                cout << "What would you like to change it to?";
                getline(cin, userInput);
                stringstream(userInput) >> requestedSeats;

                if (userCommand == 2) {
                    rowStart = requestedSeats;
                    seatStart = theater.getSeatMaxAtRow(1);
                }
                else {
                    seatStart = requestedSeats;
                    rowStart = theater.size();
                }

                //replace current theater with resized theater
                theater = theater.resize(rowStart, seatStart);
                displayTheater(theater);
                break;
            case 4:
                system("cls");
                //price is displayed under seats
                displayPrices(theater);

                cout << "Please enter all row's default price: $";
                getline(cin, userInput);

                //if the default price was a number and number only
                if (strIsNum(userInput)) {

                    cout << "Replace current costs " <<
                        "(overwrite all special prices)? Yes | No >>";
                    getline(cin, foundSeat);

                    //should the current prices 
                    //(and special rows) be replaced
                    theater.setPrice(userInput, ((toupper(foundSeat.at(0)) == 'N')));
                    displayPrices(theater);


                    //let users know it has been completed.
                    cout << "All seats now cost $" <<
                        userInput << endl;

                    cout << "Would you like to add " <<
                        "special row prices? Yes | No >>";
                    getline(cin, userInput);

                    //add special row prices
                    if (toupper(userInput.at(0)) == 'Y') {

                        cout << "Enter a list of special rows and" <<
                            " prices in R#$# format (You may " <<
                            "input multiple, spaces between " <<
                            "each input)" <<
                            endl << "ex: (R10$20 R2$21 R30$2)";
                        getline(cin, userInput);
                        ss << userInput;
                            
                        setSpeicalRows(theater, ss);
                    }

                }//strIsNum(userInput)
                else {
                    cout << "Input invalid." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }

                break;//case 4
                case 5:
                    system("cls");
                    displayTheater(theater);
                    cout << "Enter a list of seats in R#S# format " <<
                        "(You may input multiple, spaces between each input)" <<
                        endl << "ex: (R10S20 R2S21 R30S2)";
                    getline(cin, userInput);
                    ss << userInput;

                    setBlockedRows(theater, ss);
                break;

                case 6:
                    cout << "Are you sure? Yes|No: ";
                    getline(cin, userInput);

                    if (toupper(userInput.at(0)) == 'Y') {
                        theater.clear();
                    }
                break;
                case 0:
                    system("cls");
                    displayTheater(theater);

                    cout << "Would you like to save your changes? Yes|No :";
                    getline(cin, userInput);

                    if (toupper(userInput.at(0)) == 'Y') {
                        theater.save(DEFAULT_FILENAME);
                    }
                    else {
                        theater = temp;
                    }
                    break;
            default:
                break;


            }

        }
        break;//case 'N'
    default:

        break;
    }
    return 1;
}

