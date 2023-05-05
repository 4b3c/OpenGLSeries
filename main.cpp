#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(0));
	int num = rand() % 100;
	int guessed = 101;
	while (num != guessed) {
		cout << "Guess the random number: ";
		cin >> guessed;

		if (num > guessed) {
			cout << "You guessed too low..." << endl;
		} else if (num < guessed) {
			cout << "You guessed too high..." << endl;
		}

	}
	cout << "Congratulations, you got it. It was " << num << ".\n";
	return 0;
}
