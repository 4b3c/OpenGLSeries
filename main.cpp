#include <iostream>
#include <fstream>
using namespace std;

int binary_search(int arr[], int target, int low, int high) {
	int middle = (high + low) / 2; 
	if (arr[middle] == target) {
		return middle;
	} else if (arr[middle] > target) {
		return binary_search(arr, target, low, middle);
	} else {
		return binary_search(arr, target, middle, high);
	}
}

int main() {
	int target = 6;
	int array[] = {1, 4, 6, 7, 8, 10, 13, 15, 16, 17, 20, 22, 25, 26, 29, 32, 33, 34, 35, 53, 64};

	cout << binary_search(array, target, 0, (sizeof(array) / sizeof(array[0]))) << endl;

	return 0;
}