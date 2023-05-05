#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

int main() {
	unordered_map<string, int> word_freq;

	fstream file;
	string str_line;
	int lasti = 0;

	file.open("words.txt");
	getline(file, str_line);
	file.close();

	for (int i = 0; i < str_line.length(); i++) {
		if (str_line[i] == ' ' || str_line[i] == '.' || str_line[i] == ',') {
			word_freq[str_line.substr(lasti, i - lasti)] += 1;
			lasti = i + 1;
		}
	}

	for (auto const& [key, value] : word_freq) {
		cout << key << ": " << value << endl;
	}

	return 0;
}