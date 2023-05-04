#include <iostream>
#include <sstream>
using namespace std;

int main() {
	double f_temp;
	cout << "Temperature in Fahrenheit: ";
	cin >> f_temp;
	cout << "Celsius: " << (f_temp - 32) * (5.0 / 9.0) << "\n";
	
	return 0;
}
