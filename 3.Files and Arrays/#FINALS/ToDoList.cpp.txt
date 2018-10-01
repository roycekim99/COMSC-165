#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/***************************************************************
Problem: Vectors Assignment
Question:
Write a complete C++ program that will include a list of tasks in a “To Do Today” list in memory.
Make a menu that allows the user to select an option to perform using functions. 

Name: Royce Kim
ID: 1559541
Date: 07/14/2018
Status: complete
****************************************************************/

string ShowNextItem(vector<string> list) {			//Displays next item in the list, does NOT remove it.
	string item = list.size() == 0 ? "----list is empty----" : list.at(0);
	return item;
}

string ListAllItems(vector<string> list) {			//Displays all items in the list (in order)
	string completeList = "";

	for (int i = 0; i < list.size(); i++) {
		completeList += to_string(i+1) + "." + list.at(i) + "\n";
	}
	return completeList;
}

void AddToList(vector<string>& list, string item) {	//Add items to the list
	list.push_back(item);
}

string DoThis(vector<string>& list) {				//Display AND removes next item from the list
	string lastItem = ShowNextItem(list);
	if(!list.size() == 0) list.erase(list.begin());
	return lastItem;
}

string Save(vector<string> list) {					//Asks users to input file name | Saves al items to the file

	string fileName;
	cout << "What name would you like to save the list under?\n==| ";
	getline(cin, fileName);

	ofstream saveFile(fileName);

	for (int i = 0; i < list.size(); i++) {			//adds each item into text file
		saveFile << list.at(i) + "\n";
	}
	saveFile.close();
	return fileName;
}

void Load( vector<string>& list) {					//Ask user to input file name	| Loads items from file and populates the todo list with these items
	string fileName;
	string line = "";
	string item = "";	//stanford style? Personally don't like this
	
	cout << "Enter the name of the file, accuratley (with extension).\n|";
	getline(cin, fileName);
	ifstream loadingFile(fileName);

	if (loadingFile) {
		list.clear();
		while (getline(loadingFile, line)) {		//adds items into a current cleared vector
			AddToList(list, line);
		}
		cout << "Loaded!" << endl;
	}
	else
		cout << "File could not be opened." << endl; 
}

string AllDone() {
	return "Nice! You did everything on your list I assume, see you next time!";
}

void prompt() {									//Function that simply cout's the prompt. cleans up the main...	  							
	cout << "\n\t<Menu>" << endl
		<< "(enter the number correlated to the command)" << endl
		<< "1...Add to To-Do list" << endl
		<< "2...Show the next item on the To-Do list" << endl
		<< "3...Complete next item on the list (AND REMOVE)" << endl
		<< "4...LIST all items" << endl
		<< "5...SAVE current list" << endl
		<< "6...LOAD a list" << endl
		<< "7...Finish the To-Do list (quit)" << endl
		<< "=| ";
}

int main() {
	string userInput;
	string fileName = "To-Do List Savefile.txt";
	int inputNum = 0;
	vector<string> toDoList;

	cout << "Started... To-Do list application!" << endl << endl;
	
	while (inputNum != 7) {	//continue untile user inputs 7
		prompt();
		getline(cin, userInput);
		stringstream(userInput) >> inputNum;

		switch (inputNum) {
		case 1:
			cout << "What would you like to add to the list?" << endl << "==| ";
			getline(cin, userInput);

			AddToList(toDoList, userInput);
			break;

		case 2:
			cout << "The next thing you have to do is:" << endl;
			cout<< "==| " << ShowNextItem(toDoList) << endl;
			break;

		case 3:
			cout << "You just completed: "<< endl << "==| " << DoThis(toDoList) << endl;
			break;

		case 4:
			cout << endl << "\t<YOUR LIST>\n" << ListAllItems(toDoList) << endl;
			break;

		case 5:
			cout << endl << "Current list has been saved under the name " << Save(toDoList) << endl;
			break;

		case 6:
			Load(toDoList);
			break;

		case 7:	//program can still reach this case before while loop's conditional
			cout << AllDone() << endl;
			break;

		default:
			cout << "invalid number";
			break;
		}
	}

	system("pause");	//pause the console. Visual studio enterprise on windowns 10 tends to auto close after compeleting run. Can be changed in settings I think...
	return 0;
}