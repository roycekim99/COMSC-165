#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

/***************************************************************
Problem: Assignment LAB decision
Question:
An Internet service provider has three different subscription packages for its customers:
Write a program that calculates a customer�s monthly bill. It should ask which package the customer has
purchased and how many hours were used. It should then display the total amount due.

Name: Royce Kim
ID: 1559541
Date: 09/05/2018
Status: Complete
****************************************************************/

double calculate(int pkgNum, int hrSpent) {
	double finalCost = 0;

	//return initial fee if hours spent is below 10/20
	hrSpent = ((hrSpent - (pkgNum * 10)) > 0) ? hrSpent : pkgNum * 10; 
	finalCost = (9.95 + (5 * (pkgNum-1))) +	//initial cost
				((2 / pkgNum) * (hrSpent - (pkgNum * 10)));	//hourly fee
	return finalCost;
}

int main() {
	//--Variables
	char pkg = ' ';
	char compChar = ' ';
	int userHr = 0;
	int is31 = 0;
	int maxHours = 1;
	double paymentA = 0.0;
	double paymentB = 0.0;
	string month;
	string userInput;
	bool toContinue = true;
	//-----------------
	
	while (toContinue) {	//repeat code untill all inputs are valid
		do {	//prompts user untill all values are possible
			cout << "Please input: (package) (hours used) (name of this month) " << endl;
			getline(cin, userInput);

			stringstream(userInput) >> pkg >> userHr >> month;

			//see if input month has 31 days, or 30 or february
			is31 = (tolower(month.at(2)) == 'y') || (tolower(month.at(3)) == 'u') ||
				(tolower(month.at(3)) == 'c') || (tolower(month.at(3)) == 'y') ||
				(tolower(month.at(3)) == 'o') ||
				((tolower(month.at(3)) == 'e') && (tolower(month.at(0)) == 'd'));
			//return 1 if it has 31 days

			int tempint = (tolower(month.at(0)) == 'f');
			maxHours = (720 + (24 * is31)) - (48 * (tolower(month.at(0)) == 'f'));
			//february will subtract 48 from 720 = 672 hours

			switch (to_string(userHr).at(0)) { //Negative check
			case '-':
				cout << "You seem to have traveled back in time."
					" Please input a more realistic time." << endl << endl;

				userHr = 1000; //Janky way to restart loop
				break;

			default:
				cout << ((maxHours < userHr) ? "The maximum number of hours"
						 " in this month is higher than your input. "
						 "Please try again." : "Thank You") << endl << endl;

				break;
			}

		}while (maxHours < userHr);	//keep repeating until valid hour input

		paymentA = calculate(1, userHr); //cost of pkgA
		paymentB = calculate(2, userHr); //cost of pkgB

		pkg = tolower(pkg);
		switch (pkg) {
		case 'a':
			cout << "|----------------------------------|" << endl;
			cout << fixed << setprecision(2) << showpoint << "Your payment today: \t$" << paymentA << endl;

			//check to see if you HAD to pay that much
			if (userHr > 19) {
				cout << fixed << setprecision(2) << showpoint << setw(15) << "Plan B, you'd save: \t  $" <<
					(paymentA - paymentB) << endl;

				if (userHr > 25) {
					cout << fixed << setprecision(2) << showpoint << setw(15) << "Plan C, you'd save: \t  $" <<
						(paymentA - 19.95) << endl;
				}
			}

			toContinue = false; // leave masterLoop
			break;

		case 'b':
			cout << "|----------------------------------|" << endl;
			cout << fixed << setprecision(2) << showpoint << "Your payment today: \t$" << paymentB << endl;

			//check to see if you HAD to pay that much
			if (userHr < 19) {
				cout << fixed << setprecision(2) << showpoint << setw(15) << "Plan A, you'd save: \t$" <<
					(paymentB - paymentA) << endl;
			}

			if (userHr > 25) {
				cout << fixed << setprecision(2) << showpoint << setw(15) << "Plan C, you'd save: \t$" <<
					(paymentB - 19.95) << endl;
			}

			toContinue = false; // leave masterLoop
			break;

		case 'c':
			cout << "|----------------------------------|" << endl;
			cout << "Your payment today is: \t  $19.95" << endl;

			//check to see if you HAD to pay that much
			if (userHr < 25) {
				cout << fixed << setprecision(2) << showpoint << "Plan B, you'd save: \t$" <<
					(19.95 - paymentB) << endl;

				if (userHr < 19) {
					cout << fixed << setprecision(2) << showpoint << "Plan A, you'd save: \t$" <<
						(19.95 - paymentA) << endl;
				}
			}

			toContinue = false; // leave masterLoop
			break;

		default:
			cout << "But the input package unknown."
					" Please try again." << endl << endl;
			break;
		}
	}
	cout << "|----------------------------------|" << endl;

	return 0;
}