#include "board.h"

Board::Board()
{
}

Board::~Board()
{
}

Board::Board(difficulty diff)
{
	switch (diff)
	{
		case easy:
			m_sizeX = 9;
			m_sizeY = 9;
			m_numMines = 10;
			// Initialize with a predefined number of mines and grid size for easy difficulty
			break;
		case normal:
			m_sizeX = 16;
			m_sizeY = 16;
			m_numMines = 40;
			// Initialize with a predefined number of mines and grid size for normal difficulty
			break;
		case hard:
			m_sizeX = 30;
			m_sizeY = 16;
			m_numMines = 99;
			// Initialize with a predefined number of mines and grid size for hard difficulty
			break;
	}
	m_revealedTiles = 0;
}

Board::Board(int sizeX, int sizeY, int numMines)
{
	m_sizeX = sizeX;
	m_sizeY = sizeY;
	m_numMines = numMines;
	m_revealedTiles = 0;
}

int Board::getSizeX()
{
	return m_sizeX;
}
int Board::getSizeY()
{
	return m_sizeY;
}
Tile Board::getTile(int x, int y)
{
		return m_board[x][y];
}
int Board::getRevealedTiles()
{
	return m_revealedTiles;
}
int Board::getNumMines()
{
	return m_numMines;
}

void Board::initBoard(int iniX, int iniY)
{
	m_board[iniX][iniY].setType(TYPE_MINE); // Iniciar la posición inicial como mina para evitar que el jugador pierda al inicio

	int num_mines = 0;
	while (num_mines < m_numMines)
	{
		int x = rand() % m_sizeX;
		int y = rand() % m_sizeY;
		if (m_board[x][y].getType() == TYPE_EMPTY)
		{
			m_board[x][y].setType(TYPE_MINE);
			m_board[x][y].setPosition(Position(x, y));
			num_mines++;

			//m_board[x][y].getPosition().printPosition(); // Print the position of the mine (debug)
		}
	}

	m_board[iniX][iniY].setType(TYPE_EMPTY); // Iniciar la posición inicial como casilla vacía para evitar que el jugador pierda al inicio
}

void Board::showFullBoard()
{
	for (int y = 0; y < m_sizeY; y++)
	{
		for (int x = 0; x < m_sizeX; x++)
		{
			
			if (m_board[x][y].getType() == TYPE_EMPTY)
				cout << "_ ";
			else if (m_board[x][y].getType() == TYPE_MINE)
				cout << "X ";
		}
		cout << endl;
	}
}

void Board::showCurrentBoard()
{
	for (int y = 0; y < m_sizeY; y++)
	{
		for (int x = 0; x < m_sizeX; x++)
		{
			if (m_board[x][y].getIsRevealed() == true)
			{
				if (m_board[x][y].getType() == TYPE_EMPTY)
				{
					if (getAdjacentMines(x, y) > 0)
						cout << getAdjacentMines(x, y) << " "; // Mostrar casilla con el número de minas adyacentes
					else
						cout << "_ "; // Mostrar casilla vacía
				}
				else if (m_board[x][y].getType() == TYPE_MINE)
					cout << "X "; // Mostrar mina
			}
			else if (m_board[x][y].getIsFlagged() == true)
				cout << "F "; // Mostrar bandera
			else
				cout << "# "; // Mostrar casilla no revelada

		}
		cout << endl;
	}
}

int Board::getAdjacentMines(int x, int y) const
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;
			int newX = x + i;
			int newY = y + j;
			if (newX >= 0 && newX < m_sizeX && newY >= 0 && newY < m_sizeY)
			{
				if (m_board[newX][newY].getType() == TYPE_MINE)
				{
					count++;
				}
			}
		}
	}
	return count;
}

int Board::getAdjacentFlags(int x, int y) const
{
	int count = 0;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;
			int newX = x + i;
			int newY = y + j;
			if (newX >= 0 && newX < m_sizeX && newY >= 0 && newY < m_sizeY)
			{
				if (m_board[newX][newY].getIsFlagged() == true)
				{
					count++;
				}
			}
		}
	}
	return count;
}

void Board::revealTile(int x, int y)
{
	if (m_board[x][y].getType() == TYPE_EMPTY && !m_board[x][y].getIsRevealed())
	{
		m_board[x][y].setIsRevealed(true);
		m_revealedTiles++;
	}
	else
		m_board[x][y].setIsRevealed(true);

	if (m_board[x][y].getIsFlagged() == true) // Si la casilla tiene bandera, quitarla
		m_board[x][y].setIsFlagged(false);
}

bool Board::revealAdjacentTiles(int x, int y)
{
	Position pos(x, y);

	Position pendingTiles[9999];
	int n_pendingTiles = 0;
	
	pendingTiles[n_pendingTiles] = pos;
	n_pendingTiles++;

	if (m_board[x][y].getType() == TYPE_MINE) // Casilla es una mina
	{
		// Revelar todas las minas y terminar el juego
		for (int i = 0; i < m_sizeX; i++)
		{
			for (int j = 0; j < m_sizeY; j++)
			{
				if (m_board[i][j].getType() == TYPE_MINE)
					revealTile(i, j);
			}
		}
		return true; // El jugador ha perdido
	}
	else if (getAdjacentMines(x, y) == 0) // Casilla no tiene número (revelar alrededor)
	{
		while (n_pendingTiles > 0)
		{
			x = pendingTiles[0].getX();
			y = pendingTiles[0].getY();

			//cout << "--- INICIO ARRAY---" << endl; // Mostrar el array de posiciones pendientes (DEBUG)
			//for (int k = 0; k < n_pendingTiles; k++)
			//	pendingTiles[k].printPosition();
			//cout << "--- FIN ARRAY---" << endl;
			//showCurrentBoard();

			if (m_board[x][y].getIsRevealed() == false) // Si la casilla no está revelada
			{
				revealTile(x, y); // Revelar la casilla
				removeFirstPosition(pendingTiles, n_pendingTiles); // Eliminar la primera posición del array
				// Añadir las casillas adyacentes al array
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (i == 0 && j == 0) continue; // Ignorar la casilla actual
						int newX = x + i;
						int newY = y + j;
						if (newX >= 0 && newX < m_sizeX && newY >= 0 && newY < m_sizeY)
						{
							if (m_board[newX][newY].getIsRevealed() == false 
								&& m_board[newX][newY].getType() != TYPE_MINE
								&& getAdjacentMines(newX, newY) == 0)
								addLastPosition(pendingTiles, n_pendingTiles, Position(newX, newY));
							else if (m_board[newX][newY].getIsRevealed() == false
								&& m_board[newX][newY].getType() != TYPE_MINE)
								revealTile(newX, newY);
						}
					}
				}
			}
			else
				removeFirstPosition(pendingTiles, n_pendingTiles); // Eliminar la primera posición del array si ya estaba revelada
		}
		 
	}
	else if (getAdjacentMines(x, y) != 0) // Casilla tiene número
		revealTile(x, y);

	return false; // El jugador no ha perdido
}

void Board::addFlag(int x, int y)
{
	if (m_board[x][y].getIsRevealed() == false) // Si la casilla no está revelada
	{
		if (m_board[x][y].getIsFlagged() == false) // Si la casilla no tiene bandera
			m_board[x][y].setIsFlagged(true); // Añadir bandera
		else
			m_board[x][y].setIsFlagged(false); // Quitar bandera
	}
}

void Board::removeFirstPosition(Position array[], int& n_array) const
{
	if (n_array > 0)
	{
		for (int i = 0; i < n_array - 1; i++)
		{
			array[i] = array[i + 1];
		}
		n_array--;
	}
}

void Board::addLastPosition(Position array[], int& n_array, const Position& pos) const
{
	int i = 0;
	bool found = false;
	while (i < n_array && found == false)
	{
		if (array[i] == pos)
			found = true; // La posición ya existe en el array
		else
			i++;
	}
	if (found == false)
	{
		array[n_array] = pos; // Añadir la posición al final del array
		n_array++;
	}
}