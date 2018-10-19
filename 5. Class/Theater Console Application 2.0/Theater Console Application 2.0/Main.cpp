#include "Theater.h"
#include <Windows.h>

const int COLOR_BLOCKED = 12;   //red text black bg
const int COLOR_AVAILABLE = 10;   //gree text black bg
const int COLOR_TAKEN = 6;   //mustard text black bg
const int COLOR_NEUTRAL = 15;   //white text black bg

inline void ConsoleTextColor(int style = COLOR_NEUTRAL) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), style);
}

void displayTheater(Theater theater) {
    stringstream ss;
    string buffer;

    ss << theater;
    for(int i = 1; ss >> buffer; ++i) {
        cout << "Row " << setw(3) << left << i << buffer << endl;
    }
    
    
    

}

int main() {
    //testing
    Theater theater;
    ConsoleTextColor();
    displayTheater(theater);
    
    return 1;
}