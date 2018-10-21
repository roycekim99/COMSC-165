#ifndef THEATER_H
#define THEATER_H

#include "Rows.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

const int ROWS_DEFAULT = 5;    //number of rows in theater
const int SEATS_DEFAULT = 10;    //number of seats per row

class Theater {
private:
    vector <Row> theater;
    string name;


public:
    //constructor
    Theater(string name = "Untitled", int rows = ROWS_DEFAULT, int seats = SEATS_DEFAULT) {
        this->name = name;

        for (int i = 0; i < rows; ++i) {
            Row temp(seats);
            theater.push_back(temp);
        }

    }

    //::load from file
    bool load(const string& fileName) {
        string buffer;
        ifstream inputFile(fileName);
        int splitPos = 0;
        Row temp;

        if (inputFile) {
            theater.clear();

            getline(inputFile, buffer);
            name = buffer;

            getline(inputFile, buffer);
            splitPos = buffer.find('$');
            temp = Row(buffer.substr(0, splitPos),
                       buffer.substr(splitPos + 1, (buffer.size() - (splitPos))));
            theater.push_back(temp);

            while (getline(inputFile, buffer)) {
                temp = Row(buffer.substr(0, splitPos),
                           buffer.substr(splitPos + 1, (buffer.size() - (splitPos))));
                theater.push_back(temp);
            }
            inputFile.close();
            return 1;
        }
        else {
            inputFile.close();
            return 0;
        }

    }

    //::save to file
    bool save(const string& fileName) {
        ofstream outputFile(fileName);

        if (outputFile) {
            outputFile << name << endl;
            for (Row r : theater) {
                outputFile << r.info() << "$" << r.getPrice() << endl;
            }

            outputFile.close();
            return 1;
        }
        else {
            outputFile.close();
            return 0;
        }
    }
    

    //::return size of theater
    int size() {
        return theater.size();
    }

    //::return max number of seats at given row (should be equal at all seats)
    int getSeatMaxAtRow(int rowNum) {
        return ((rowNum < theater.size() && rowNum>=0) ? theater.at(rowNum).size() : -1);
    }

    //::update a seat
    bool updateSeat(int row, int seat, Status s) {
        
        bool success = ( (row > 0 && row <= theater.size()) &&
            (seat > 0 && seat <= getSeatMaxAtRow(row-1)) );

        //validate inputs
        if (success) {
            theater.at(row - 1).updateSeat(seat, s);
        }
        
        return success;
    }

    //::resize theater without losing current status
    Theater resize(int newRows, int newSeatMax, bool replace = true) {
        //decide which size is smaller
        int maxRows = (theater.size() > newRows) ? newRows : theater.size();
        int maxSeats = (getSeatMaxAtRow(1) > newSeatMax) ? newSeatMax : getSeatMaxAtRow(1);

        //fill newtemp Theater object with available seats
        Theater tempTheater(name, newRows, newSeatMax);

        //update new theater with old data
        if (replace) {
            for (int r = 1; r <= maxRows; ++r) {
                for (int s = 1; s <= maxSeats; ++s) {
                    //set status of each seat in row
                    tempTheater.updateSeat(r, s, theater.at(r - 1).getStatusAt(s));
                    //set price of seats in row
                    tempTheater.setPrice(r, theater.at(r - 1).getPrice());
                }
            }
        }
        //update current vector with new vector
        return tempTheater;
    }

    //::rename current theater
    void rename(string newName) {
        name = newName;
    }

    //::return name of theater
    string getName() {
        return name;
    }

    //::get Row
    Row getRow(int r) {
        return theater.at(r - 1);
    }

    //::set price of rows in theater
    //::::OF ALL ROWS
    void setPrice(const string& newPrice, bool replace = false) {
        //replace all non special prices
        for (Row &r : theater) {
            if (!r.isSpecial() || !replace) {
                r.setPrice(newPrice);
            }
            
        }
    }
    //::::OF SINGLE ROW
    void setPrice(int row, const string& newPrice, bool isSpecial = false) {
        theater.at(row - 1).setPrice(newPrice, isSpecial);        
    }

    //::get prices
    string getPrice(int rowNum) {
        return theater.at(rowNum-1).getPrice();
    }
    
    //::find seat from a row
    string findSeats(int numberOfSeatsRequestd = 1, int rowStart = 1, bool oneLine = false) {
        bool found = false;
        int foundSeat = 0;
        int foundRow = 0;
        string finalOutput = "Not Found";
        stringstream ss;

        if ( (rowStart > 0 && rowStart <= theater.size() )&& (numberOfSeatsRequestd >= 0 && numberOfSeatsRequestd <= theater.at(0).size()) ) {
            for (int i = rowStart - 1;( (oneLine) ?
                  (i = rowStart) : i < theater.size() )  &&
                   !found; ++i) {

                foundSeat = theater.at(i).findSeatNumber(numberOfSeatsRequestd);

                if (foundSeat >= 0) {
                    found = true;
                    foundRow = i + 1;
                    ss << "R" << foundRow << "S" << foundSeat;
                }
            }

            ss >> finalOutput;
        }
        
        return finalOutput;
    }

    //::calculate total price of theater
    string calculateTotalPrice() {
        double price = 0.0;
        double totalPrice = 0.0;
        stringstream converterStream;
        string buffer;
        char dum = ' ';

        for (Row r : theater) {
            //findprice
            converterStream << r.getPrice();
            converterStream >> price;
            cout << price << ":" << r.getPrice() << endl;  //debug
            totalPrice += (r.soldSeats() * price);
            
            converterStream.str("");
        }

        converterStream << totalPrice;
        converterStream >> buffer;
        return buffer;
    }

    //::clear theater to default
    void clear() {
        theater.clear();
    }

    //::OVEERRIDE = operator
    void operator= (const Theater& rightTheater) {
        name = rightTheater.name;
        theater = rightTheater.theater;
        
    }

    //::OVERRIDE << operator
    friend ostream& operator<< (ostream &strm, const Theater& theaterObject) {
        for (Row r : theaterObject.theater) {
            strm << r << endl;
        }
        return strm;
    }

};
#endif // !THEATER_H