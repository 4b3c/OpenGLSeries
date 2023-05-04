#include <iostream>
#include <sstream>
using namespace std;

int main() {
	double sales = 95000;
	double state_tax = 0.04 * sales;
	double county_tax = 0.02 * sales;
	cout << "Sales: " << sales << endl;
	cout << "State Tax: " << state_tax << endl;
	cout << "County Tax: " << county_tax << endl;
	cout << "Total Profit: " << sales - state_tax - county_tax << endl;
	return 0;
}
