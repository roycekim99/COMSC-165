#include <iostream>
#include <sstream>
using namespace std;

void reverseDisplay(int value) {
	if (value < 10)		//when the user inputs a single digit number
		cout << value << endl;
	else{
		cout << (value%10);		//displays the last digit of the int
		reverseDisplay(value / 10);	
	}
}

int main1() {
	cout << "Input a number to reverse:" << endl <<"(for the sake of simplicity please input a valid integer: 1,2,3,4,5,6,7,8,9 or 0)" << endl << "==| ";
	
	int inputNum;
	string tempInput;
	getline(cin, tempInput);

	stringstream(tempInput) >> inputNum;

	reverseDisplay(inputNum);
	system("pause");
	return 0;
}