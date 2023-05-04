#include <iostream>

using namespace std;

int main() {
	int a = 1;
	int b = 2;

	int c = a;
	a = b;
	b = c;
	
	cout << b;

	return 0;
}