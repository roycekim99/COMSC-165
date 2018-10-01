// This program lets the user enter a filename.
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
   ofstream outputFile;
   string filename;
   int number1,number2,number3;

   // Get the filename from the user.
   cout << "Enter the filename: ";
   getline(cin, filename);

   // Open the file.
   outputFile.open(filename);

   // If the file successfully opened, process it.
   if (outputFile)
   {
     cout <<endl << "input 3 integers : ";
     cin >> number1 >> number2 >>number3;

     outputFile<<number1<<endl<<number2<<endl<<number3;

      // Close the file.
      outputFile.close();
   }
   return 0;
}
