#include <iostream>
#include <fstream>
using namespace std;

bool palindrome(string word) {
	for (int i = 0; i < word.length() / 2; i++) {
		if (word[i] != word[word.length() - i - 1]) {
			cout << word[i] << " isn't " << word[word.length() - i - 1] << endl;
			return false;
		}
	}
	return true;
}

int main() {
	string word;
	cout << "Enter a word: ";
	cin >> word;

	if (palindrome(word)) {
		cout << "The word '" << word << "' is a palindrome!" << endl;
	} else {
		cout << "The word '" << word << "' isn't a palindrome." << endl;
	}

	return 0;
}