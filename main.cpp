#include <iostream>
#include <bitset>
using namespace std;

// represents the tictactoe board
string board[5] = {
	"   |   |   ",
	"---|---|---",
	"   |   |   ",
	"---|---|---",
	"   |   |   "
};

// function to draw the tictactoe board
void print_board(string current_board[], int num_rows) {
	for (int i = 0; i < num_rows; i++) {
		cout << current_board[i] << endl;
	}
}

// takes the moves of each player, and checks if they match a win condition
int check_win(int played[]) {

	// win possibilities represented in binary for bit manipulation for a faster game
	int wins[] = {
		0b111000000, 0b000111000, 0b000000111,
		0b100100100, 0b010010010, 0b001001001,
		0b100010001, 0b001010100
	};

	// this uses an and gate to add the players moves and win conditions
	// if the "anded" value of that is the win condition it means the player had all positions for that win
	// we return 1 for a win by player1, etc, and 0 for no win
	for (int i = 0; i < 8; i++) {
		if ((played[0] & wins[i]) == wins[i]) {
			return 1;
		} else if ((played[1] & wins[i]) == wins[i]) {
			return 2;
		}
	}

	return 0;
}

// main function
int main() {
	int move;
	int move_mask = 0;
	int move_count = 0;
	int player = 0;
	int winner = 0;
	int spots[] = {0, 0};
	char tokens[] = {'x', 'o'};

	// main loop that only ends by break
	while (1 == 1) {
		// start each round by printing the board
		print_board(board, 5);

		// wait for a valid position to be selected
		while (1 == 1) {
			cout << "Enter a number 1-9 for " << tokens[player] <<"'s position: ";
			cin >> move;
			// using binary to represent the move so we can easily check if its been made before
			move_mask = 512 >> move;

			// make sure its a valid position
			if (move < 1 || move > 9) {
				cout << "The chosen position isn't valid.\n";
			// make sure the move hasn't been made before, by either player	
			} else if ((spots[0] & move_mask) > 0 || (spots[1] & move_mask) > 0) {
				cout << "The chosen position is taken.\n";
			// otherwise, add the move to the players bit moves and exit this loop	
			} else {
				spots[player] |= move_mask;
				break;
			}

		}

		// add the player's token (x or o) to the board in the selected position
		board[((move - 1) / 3) * 2][static_cast<int>(((move + 2) % 3) * 4) + 1] = tokens[player];

		// change player (1 -> 0; 0 -> 1;)
		player = (player * -1) + 1;

		// count how many moves have taken place
		move_count += 1;
		if (move_count > 4) {
			// after 5 moves, wins can happen so check
			winner = check_win(spots);
			if (winner != 0) {
				// a player won, print congrats message
				print_board(board, 5);
				cout << "\nLooks like player " << tokens[winner - 1] << " wins!! Congrats!\nGame over!\n";
				break;
			}
		}
		if (move_count > 8) {
			// after 9 moves, we know nobody is going to win so end the game
			cout << "\nLooks like a tie.. Better luck next time.\nGame over!\n";
			break;
		}

	}
	
	// c++ is weird
	return 0;
}