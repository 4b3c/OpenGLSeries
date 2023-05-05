#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

string words[110];
int word_count[110];

void bubblesort(string words1[], int word_count1[], int arr_len) {
	bool changed = true;
	cout << "Starting sort.\n";
	while (changed == true) {
		changed = false;
		for (int i = 0; i < arr_len - 1; i++) {
			if (word_count1[i] > word_count1[i + 1]) {
				swap(word_count1[i], word_count1[i + 1]);
				swap(words1[i], words1[i + 1]);
				changed = true;
			} else {
			}
		} 
	}
	cout << "Done sorting.\n";
}

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

	string words[word_freq.size()];
	int word_count[word_freq.size()];
	int i = 0;

	for (auto const& [key, value] : word_freq) {
		words[i] = key;
		word_count[i] = value;
		i++;
	}

	bubblesort(words, word_count, sizeof(word_count) / sizeof(word_count[0]));

	for (int i = 0; i < sizeof(word_count) / sizeof(word_count[0]); i++) {
		cout << words[i] << ": " << word_count[i] << endl;
	}


	return 0;
}