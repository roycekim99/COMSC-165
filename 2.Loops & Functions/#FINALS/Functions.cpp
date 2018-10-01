#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int flip(int number) {  //Palindrome
    int newNum = 0, i = 0, remainder;
    do {
        newNum = newNum * 10 + number % 10;
    }
    while (number /= 10);

    return newNum;
}

bool isPalindrome(int number) { //Palindrome
    return (number == flip(number));
}

string swapCases(const string& s) { //SwapCases
    string tempString = s;

    for (int i = 0; i < s.size(); i++) {
        (isupper(s.at(i))) ? tempString.at(i) = tolower(s.at(i)) :
            tempString.at(i) = toupper(s.at(i));
    }

    return tempString;
}

int getNumber(char uppercaseLetter) {   //PhoneNumber
    return (((uppercaseLetter - 59) / 3) - ((uppercaseLetter == 'S') ||
                                            (uppercaseLetter == 'V') ||
                                            (uppercaseLetter == 'Y') ||
                                            (uppercaseLetter == 'Z')));
}

int main() {
    //---Variables
    char userChar = ' ';
    string tempString = "";
    string finalString = "";
    string userInput = "";
    int userNum = 0;
    stringstream ss(tempString);
    //--

    //--Not part of assignment
    cout << "Enter a problem number (1,3,4) | 0 to quit" << endl;
    getline(cin, userInput);
    stringstream(userInput) >> userNum;

    switch (userNum) {
        case 1: //Palindrome
            cout << "Input a number to check if it is a palindrome number: ";
            getline(cin, userInput);
            cout << endl;

            stringstream(userInput) >> userNum;
            cout << "The number is " <<
                    (isPalindrome(userNum) ? "" :
                    "not") << " a palindrome" << endl;
            break;

        case 3: //SwapCases
            cout << "Enter a string to switch cases: ";
            getline(cin, userInput);
            cout << endl;

            cout << "You entered: " << userInput <<
                 endl << "Swaped: " << swapCases(userInput) << endl;
            break;

        case 4: //Phone number
            cout << "Input a phone number: ";
            getline(cin, userInput);
            cout << endl;

            for (int i = 0; i < userInput.size(); i++) {
                if (isalpha(userInput.at(i)) ){
                    ss << getNumber(toupper(userInput.at(i)));
                    ss >> tempString;
                }
                else {
                    tempString = userInput.at(i);
                }

                finalString += tempString;
                ss.clear();
            }
            cout << finalString << endl;
            break;

        default:
            break;
    }
    return 0;
}