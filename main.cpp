#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	int number;
	cout << "Give me a number: ";
	cin >> number;
	if ((number % 2) == 0) {
		cout << "Even!";
	} else {
		cout << "Odd!";
	}
	return 0;
}
