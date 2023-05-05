#include <iostream>
#include <bitset>
using namespace std;

string board[5] = {
	"   |   |   ",
	"---|---|---",
	"   |   |   ",
	"---|---|---",
	"   |   |   "
};

void print_arr(int array[], int length) {
	cout << "{";
	for (int i = 0; i < length; i++) {
		cout << array[i];
		if (i != length - 1) {
			cout << ", ";
		}
	}
	cout << "}\n";
}


void print_board(string current_board[], int num_rows) {
	for (int i = 0; i < num_rows; i++) {
		cout << current_board[i] << endl;
	}
}

int check_win(int played[]) {
	int wins[] = {
		0b111000000, 0b000111000, 0b000000111,
		0b100100100, 0b010010010, 0b001001001,
		0b100010001, 0b001010100
	};

	int bit_mask = 0;
	int player1 = 0;
	int player2 = 0;

	for (int i = 0; i < 9; i++) {
		if (played[i] == 1) {
			bit_mask = 256 >> i;
			player1 |= bit_mask;
		} else if (played[i] == 2) {
			bit_mask = 256 >> i;
			player2 |= bit_mask;
		}
	}

	for (int i = 0; i < 8; i++) {
		if ((player1 & wins[i]) == wins[i]) {
			return 1;
		} else if ((player2 & wins[i]) == wins[i]) {
			return 2;
		}
	}

	return 0;
}

int main() {
	int move;
	int move_count = 0;
	int player = 0;
	int winner = 0;
	int spots[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	char tokens[] = {'x', 'o'};


	while (1 == 1) {
	print_board(board, 5);

		while (1 == 1) {
			cout << "Enter a number 1-9 for " << tokens[player] <<"'s position: ";
			cin >> move;
			if (move > 0 && move < 10 && spots[move - 1] == 0) {
				break;
			} else {
				cout << "The chosen number isn't valid or is taken.\n";
			}
		}

		board[((move - 1) / 3) * 2][static_cast<int>(((move + 2) % 3) * 4) + 1] = tokens[player];
		spots[move - 1] = 1 + player;
		player = (player * -1) + 1;
		move_count += 1;
		if (move_count > 4) {
			winner = check_win(spots);
			if (winner != 0) {
				cout << "\nLooks like player " << tokens[winner - 1] << " wins!! Congrats!\n";
				cout << "Game over!\n";
				break;
			}
		}

	}
	
	return 0;
}