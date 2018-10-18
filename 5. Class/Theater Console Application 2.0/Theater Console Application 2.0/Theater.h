#ifndef THEATER_H
#define THEATER_H

#include <Windows.h>
#include <vector>

const char AVAILABLE = '#';
const char TAKEN = '-';
const char BLOCKED = 'X';
const int ROWS_DEFAULT = 10;    //number of rows in theater
const int SEATS_DEFAULT = 5;    //number of seats per row
const int BLOCKED_COLOR = 12;   //red text black bg

inline void ConsoleTextColor(int style) {
    SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), style );
}

struct Row {
private:
    std::string content;
    
public:

    Row(int seats) {//constructor
        for (int i = 0; i < seats; ++i) {
            content.push_back(AVAILABLE);
        }
    }

    //get length of row (number of seats at row)
    int size() {  
        return content.size();
    }

    void updateSeat(int seatNumber, int status) {
        char newStatus = '#';

        switch (status) {
        case 1:
            newStatus = TAKEN;
            break;
        case 2:
            newStatus = BLOCKED;
            break;
        default:
            break;
        }

        content.replace(seatNumber - 1, 1, 1, newStatus);
    }

    char getStatusAt(int seatNum) {
        return content.at(seatNum - 1);
    }

    
};


class Theater {
private:
    std::vector <Row> theater;
    std::string name;

public:
    
    Theater(std::string name = "Untitled", int rows = ROWS_DEFAULT, int seats = SEATS_DEFAULT) {   //initilaize theater 
        this->name = name;
        theater.resize(rows);

        for (int i = 0; i < rows; ++i) {
            Row temp(seats);
            theater.push_back(temp);
        }
    }

    //***********************************************************************

    void rename(string newName) {
        name = newName;
    }

    int getRows() {
        return theater.size();
    }

    int getSeatMaxAtRow(int rowNum) {
        return ( (rowNum < theater.size() && rowNum)? theater.at(rowNum).size() : -1 );
    }

    void scaleAndReplace(int newRows, int newSeatMax, bool replace = true) {

        Theater temp(name,newRows, newSeatMax);

        for (int r = 0; r < newRows; ++r) {
            for (int s = 0; s < newSeatMax; ++s) {
                
            }
        }

    }

};


#endif // !THEATER_H

