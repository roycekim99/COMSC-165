#ifndef SEAT_H
#define SEAT_H

const char AVAILABLE = '#';
const char TAKEN = '-';
const char BLOCKED = 'X';

class Seat {
private:
    char status;
    

public:

    Seat() {
        status = AVAILABLE;
    }

    void updateSeat(int status) {   //set status

        switch (status) {
        case 0:
            status = AVAILABLE;
            break;
        case 1:
            status = TAKEN;
            break;
        case 2:
            status = BLOCKED;
        default:
            break;
        }
    }

    char getStatus() {  //return status
        return status;
    }



};



#endif // !SEAT_H
