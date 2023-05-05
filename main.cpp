#include <iostream>
#include <fstream>
using namespace std;

int main() {
	fstream file;
	string str_line;
	double line;
	int max = 0;
	int min = 100;
	int count = 0;
	double tot = 0;

	file.open("numbers.txt");

	while(getline(file, str_line)) {
		line = stoi(str_line);
		if (line > max) {
			max = line;
		}
		if (line < min) {
			min = line;
		}
		tot += line;
		count += 1;
	}

	cout << "Maximum value: " << max << endl;
	cout << "Minimum value: " << min << endl;
	cout << "Average value: " << tot / count << endl;

	return 0;
}