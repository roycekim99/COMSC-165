#ifndef THEATER_H
#define THEATER_H

#include "Rows.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

const int ROWS_DEFAULT = 5;    //number of rows in theater
const int SEATS_DEFAULT = 10;    //number of seats per row

class Theater{
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

    //::return size of theater
    int size() {
        return theater.size();
    }

    //::return max number of seats at given row (should be equal at all seats)
    int getSeatMaxAtRow(int rowNum) {
        return ( (rowNum < theater.size() && rowNum)? theater.at(rowNum).size() : -1 );
    }

    //::update a seat
    bool updateSeat(int row, int seat, char status) {
        bool success = (row >= 0 && row <= theater.size()) &&
            (seat >= 0 && seat <= getSeatMaxAtRow(row));

        //validate inputs
        if (success) {
            theater.at(row).updateSeat(seat, status);
        }
        return success;
    }

    //::resize theater without losing current status
    void resize(int newRows, int newSeatMax, bool replace = true) {
        //decide which size is smaller
        int maxRows = (theater.size() > newRows) ? newRows : theater.size();
        int maxSeats = (getSeatMaxAtRow(1) > newSeatMax) ? newSeatMax : getSeatMaxAtRow(1);

        //fill newtemp Theater object with available seats
        Theater tempTheater(name, maxRows, maxSeats);

        //update new theater with old data
        if (replace) {
            for (int r = 0; r < maxRows; ++r) {
                for (int s = 0; s < maxSeats; ++s) {
                    tempTheater.updateSeat(r, s, theater.at(r).getStatusAt(s));
                }
            }
        }
        //update current vector with new vector
        this->theater = tempTheater.theater;
    }

    //::rename current theater
    void rename(string newName) {
        name = newName;
    }

    //::get Row
    Row &getRow(int r) {
        return theater.at(r-1);
    }

    //::set price of rows in theater
    void setPrice(const string& newPrice) {
        for (Row r : theater) {
            r.setPrice(newPrice);
        }
    }

    //::get prices

    //::OVERRIDE << operator
    friend ostream& operator<< (ostream &strm, const Theater& theaterObject) {
        for (Row r: theaterObject.theater) {
            strm << r << endl;
        }
        return strm;
    }

};

#endif // !THEATER_H