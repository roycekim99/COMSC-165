#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
  fstream inout;

 
  // Append to the file
  inout.open("city.txt", ios::out | ios::app);

  // Write cities
  inout << "Savannah" << " " << "Austin" << " " << "Chicago";

  inout.close();

  string city;

  // Open the file
  inout.open("city.txt", ios::in);
  while (!inout.eof()) // Continue if not end of file
  {
    inout >> city;
    cout << city << " ";
  }

  inout.close();

  return 0;
} 
