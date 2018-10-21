#ifndef ROWS_H
#define ROWS_H

#include <string>
using namespace std;

const string PRICE_DEFAULT = "11.00";
enum class Status : char{
    AVAILABLE = '#',
    TAKEN = '*',
    BLOCKED = 'X'
};


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
            givenRow.push_back(static_cast<char>(Status::AVAILABLE) );
        }
    }

    Row(const string& inputString, string p = PRICE_DEFAULT) {
        givenRow = inputString;
        price = p;
    }

    //::get number of sold seats
    int soldSeats() {
        int count = 0;

        for (char s : givenRow) {
            count += (s == static_cast<char>(Status::TAKEN));
        }

        return count;
    }

    //::get max number of seats per row
    int size() {
        return givenRow.size();
    }

    //::set status at given seat number
    void updateSeat(int seatNumber, Status s) {
        givenRow.replace(seatNumber - 1, 1, 1, static_cast<char>(s));
    }

    //::get status at given seat number
    Status getStatusAt(int seatNum) {
        Status stat = Status::AVAILABLE;

        switch (givenRow.at(seatNum - 1)) {
        case (static_cast<char>(Status::BLOCKED)):
            stat = Status::BLOCKED;
            break;
        case (static_cast<char>(Status::TAKEN)):
            stat = Status::TAKEN;
            break;
        default:
            break;
        }
        return stat;
    }

    //::get "givenRow"
    string info() {
        return givenRow;
    }

    //::get price of row
    string getPrice() {
        return price;
    }

    //::set price of row
    void setPrice(const string& p, bool isSpecial = false) {
        price = p + ( (isSpecial)? "*" : "");
    }

    //::find available seat
    int findSeatNumber(int numberOfSeatsRequested = 1) {
        string requestedChars = "";
        int position = 0;

        for (int i = 1; i <= numberOfSeatsRequested; ++i) {
            requestedChars += static_cast<char>(Status::AVAILABLE);
        }
        
        position = givenRow.find(requestedChars);

        return (position);
    }

    //::get if row price is special
    bool isSpecial() {
        return (price.find('*') == (price.size()-1));
    }

    //::OVERRIDE << operator
    friend ostream& operator<< (ostream& strm, const Row& r) {
        return strm << r.givenRow <<"-$" << r.price;
    }

};

#endif // !ROWS_H
