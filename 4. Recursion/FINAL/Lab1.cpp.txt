#include <iostream>
using namespace std;

double sumSeries(double i) {
		return (i==1)? .333333 : (i / ((2 * i) + 1))+ sumSeries(i-1);
}

int main() {
	for (int i = 1; i <= 10; i++) {
		cout << "Sum for " << i << ": " << sumSeries(i) << endl;
	}
	system("pause");
	return 0;
}