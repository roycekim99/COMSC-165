#ifndef ROWS_H
#define ROWS_H

#include <string>

using namespace std;

const string PRICE_DEFAULT = "11.00";
const char AVAILABLE = '#';
const char TAKEN = '-';
const char BLOCKED = 'X';

//contains row information, including price
class Row {
private:
    string price;
    string givenRow;

public:
    //constructor
    Row(int seats = 5, string p = PRICE_DEFAULT) {//constructor
        price = p;

        for (int i = 0; i < seats; ++i) {
            givenRow.push_back(AVAILABLE);
        }
    }

    //::get max number of seats per row
    int size() {
        return givenRow.size();
    }

    //::set status at given seat number
    //TODO: let user pick enum
    void updateSeat(int seatNumber, char status) {
        //probably better to use enum.
        char newStatus = '#';

        switch (toupper(status)) {
        case '-':
            newStatus = TAKEN;
            break;
        case 'X':
            newStatus = BLOCKED;
            break;
        default:
            break;
        }

        givenRow.replace(seatNumber - 1, 1, 1, newStatus);
    }

    //::get status at given seat number
    char getStatusAt(int seatNum) {
        return givenRow.at(seatNum - 1);
    }

    //::get "givenRow"
    string getRow() {
        return givenRow;
    }

    //::get price of row
    string getPrice() {
        return price;
    }

    //::set price of row
    void setPrice(const string& p) {
        price = p;
    }

    //::OVERRIDE << operator
    friend ostream& operator<< (ostream& strm, const Row& r) {
        return strm << r.givenRow <<"-$" << r.price;
    }

};

#endif // !ROWS_H
