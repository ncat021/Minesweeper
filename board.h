#include <random>
#include "tile.h"

int const MAX_X_SIZE = 100;
int const MAX_Y_SIZE = 100;
int const MAX_NUM_MINES = 9999;

enum difficulty
{
	easy,
	normal,
	hard
};

class Board
{
public:
	// Constructors and Destructor
	Board();
	~Board();
	Board(difficulty diff);
	Board(int sizeX, int sizeY, int numMines);

	int getSizeX();
	int getSizeY();
	Tile getTile(int x, int y);
	int getRevealedTiles();
	int getNumMines();

	/*
	Inicializa el tablero con minas aleatorias
	*/
	void initBoard(int iniX, int iniY);
	
	/*
	Muestra el tablero completo (solo minas y blancas)
	*/
	void showFullBoard();

	/*
	Muestra el tablero actual
	*/
	void showCurrentBoard();

	/*
	Revela la casilla en las coordenadas (x, y) y las casillas adyacentes si es necesario, devuelve true si el jugador pierde
	*/
	bool revealAdjacentTiles(int x, int y);

	/*
	Añade una bandera a la casilla en las coordenadas (x, y)
	*/
	void addFlag(int x, int y);

	/*
	Devuelve la cantidad de minas adyacentes a una casilla determinada por sus coordenadas (x, y)
	*/
	int getAdjacentMines(int x, int y) const;
	

private:
	Tile m_board[MAX_X_SIZE][MAX_Y_SIZE];
	int m_sizeX;
	int m_sizeY;

	int m_numMines;
	int m_revealedTiles;
	
	

	/*
	Devuelve las banderas adyacentes a una casilla determinada por sus coordenadas (x, y)
	*/
	int getAdjacentFlags(int x, int y) const;

	/*
	Revela la casilla en las coordenadas (x, y)
	*/
	void revealTile(int x, int y);

	/*
	Devuelve el array con la primera posición eliminada
	*/
	void removeFirstPosition(Position array[], int& n_array) const;

	/*
	Añade una posición al final del array
	*/
	void addLastPosition(Position array[], int& n_array, const Position& pos) const;
};