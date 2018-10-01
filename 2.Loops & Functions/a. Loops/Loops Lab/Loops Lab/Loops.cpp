#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <random>
using namespace std;

/***************************************************************
Problem: Loops Assignemnt Questiosn 1-4
Question: 
1.Write a program that prompts the user to enter an integer from 1 to 9 and displays a pyramid, as shown in the following
sample run:

2.Write a program that generates a random number between 1...100 and asks the user to guess what the number is. 

3.Write a program that prompts the user to enter a string and displays the number of the uppercase letters in the string. 

4.A string is a palindrome if it reads the same forward and backward. The words “mom,” “dad,” and “noon,” for example,
are palindromes

Name: Royce Kim
ID: 1559541
Date: 09/11/2018
Status: complete
****************************************************************/

void doPyramid() {    //ASSIGNMENT 1
    string numbers = "9 8 7 6 5 4 3 2 1 2 3 4 5 6 7 8 9";
    string userInput;
    int maxNum = 0;

    cout << "Pyramid Building People That Are Kind of International" <<
        endl << "Enter the number of lines: ";
    getline(cin, userInput);

    stringstream(userInput) >> maxNum;
    
    /**Uses iomanip to align numbers to right    

    1. Determine space needed for first line 
        relative to user's input number
    2. Determine what numbers to show from 'numbers'
        relative to needed to display line number (i)
    3. Determine how long the substring must be depending on (i)

    **/

    for (int i = 1; i <= maxNum; i++) { 
        cout << setw(((2 * maxNum) - 3) + (2 * (i))) << right <<
                numbers.substr((18 - (2 * i)), (4 * i) - 3) 
                << endl;
    }
}

void doRandon() {    //ASSIGNMENT 2
    //Initialize 
    random_device rd; 
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(1, 100);
    int compNum = distribution(generator);
    //
    string streamInput;
    int userGuess = 0;
    int gueses = 0;

    cout << "The computer just picked a number" <<
        " between 1-100 inclusive." << endl <<
        "Enter your guess here ==| ";
    getline(cin, streamInput);
    stringstream(streamInput) >> userGuess;

    do {
        cout << ((userGuess < compNum)? "Too low, try again!" :
                  "Too high, one more time!") << endl;
        cout << "==| ";
        getline(cin, streamInput);
        stringstream(streamInput) >> userGuess;
        gueses++;

    }while (userGuess != compNum);

    cout << "Nice! Took you " << gueses << " tries!" << endl;
}

void countUpper() {    //ASSIGNMENT 3
    string userInput;
    int count = 0;

    cout << "Enter a string to count uppercases." << endl;
    getline(cin, userInput);

    for (int i = 0; i < userInput.size(); i++) {
        count += ( userInput.at(i) == toupper(userInput.at(i)) &&
                  userInput.at(i) != ' ' );
    }
    
    cout << "There are " << count << 
            " capital letters in that sentence." << endl;
}

void palindrome() {    //ASSIGNMENT 4
    string userInput, palindrome = "";
    int isPalindrome = 0;

    cout << "Enter a palindrome string: ";
    getline(cin, userInput);

    //Uppercase all letters
    for (int i = 0; i < userInput.size(); i++) { 
        userInput.at(i) = toupper(userInput.at(i));
    }

    isPalindrome = !(userInput.compare( 
        string(userInput.rbegin(), userInput.rend()) 
    ));    
    //when 1, is palidrome. if 0 not.

    cout << "This is " << ((isPalindrome) ? "" : "not ") << "a palindrome";
}

int main() {

    int probNum;
    string tempInput;

    do {
        cout << endl;
        cout << "Enter the problem number (1~4 | 0 to quit): ";
        getline(cin, tempInput);
        stringstream(tempInput) >> probNum;

        switch (probNum) {
        case 1:
            cout << endl;
            doPyramid();
            break;
        case 2:
            cout << endl;
            doRandon();
            break;
        case 3:
            cout << endl;
            countUpper();
            break;

        case 4:
            cout << endl;
            palindrome();
            break;

        case 0:
            break;
        default:
            cout << "Invalid number." << endl;
            break;
        }

    }
    while (probNum != 0);

    system("pause");
    return 0;
}