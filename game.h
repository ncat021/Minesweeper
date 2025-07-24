#include "board.h"

enum gameState
{
	playing,
	won,
	lost
};

bool chooseDifficulty(Board& board)
{
	int choice;
	cout << "---SELECCIONA LA DIFICULTAD---\n";
	cout << "1. Easy\n";
	cout << "2. Normal\n";
	cout << "3. Hard\n";
	cout << "4. Custom\n";
	cin >> choice;
	switch (choice)
	{
		case 1: 
			board = Board(easy); 
			return true;
		case 2:
			board = Board(normal); 
			return true;
		case 3: 
			board = Board(hard); 
			return true;
		case 4:
			int sizeX, sizeY, numMines;
			cout << "Enter board size (width height): ";
			cin >> sizeX >> sizeY;
			cout << "Enter number of mines: ";
			cin >> numMines;
			if (sizeX > 0 && sizeY > 0 && numMines > 0 
				&& numMines <= sizeX * sizeY
				&& sizeX <= MAX_X_SIZE && sizeY <= MAX_Y_SIZE)
			{
				board = Board(sizeX, sizeY, numMines);
				return true;
			}
			else
			{
				cout << "Invalid custom settings.\n";
				return false;
			}
		default:
			cout << "Invalid choice.\n";
			return false;
	}
}

void selectTile(int& x, int& y, Board& board)
{
	bool valid = false;
	while (!valid)
	{
		cout << "Enter tile coordinates (x y): ";
		cin >> x >> y;

		if (x >= 0 && x < board.getSizeX() && y >= 0 && y < board.getSizeY())
			valid = true;
		else
			cout << "Invalid coordinates. Please try again.\n";
	}
}

void showGameOverMessage(gameState state)
{
	if (state == won)
		cout << "Congratulations! You've won the game!\n";
	else if (state == lost)
		cout << "Game Over! You hit a mine.\n";
}

void mainGame()
{
	srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

	Board board;
	gameState state = playing;
	int x, y;

	bool valid;

	// Select difficulty
	valid = chooseDifficulty(board);
	while (!valid)
		valid = chooseDifficulty(board);

	// Init board
	board.showCurrentBoard();
	selectTile(x, y, board);
	board.initBoard(x, y);

	// Main game loop
	while (state == playing)
	{
		board.revealAdjacentTiles(x, y);
		board.showCurrentBoard();
		if (board.revealAdjacentTiles(x, y)) // Jugador toca una mina y pierde
			state = lost;
		else if (board.getRevealedTiles() == (board.getSizeX() * board.getSizeY() - board.getNumMines())) // Jugador gana
			state = won;
		else
			selectTile(x, y, board);
	}

	showGameOverMessage(state);

}

void debugGame()
{
	srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

	int x = 0;
	int y = 0;
	cin >> x >> y;

	Board board;
	difficulty diff = hard; // Change difficulty here: easy, normal, hard
	board = Board(diff);

	board.initBoard(x, y);
	board.showFullBoard();

	while (true)
	{
		board.revealAdjacentTiles(x, y);
		board.showCurrentBoard();
		cin >> x >> y;
	}
}