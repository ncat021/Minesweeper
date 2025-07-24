#include <vector>
#include <iostream>
using namespace std;

class Position
{
public:
	Position();
	Position(int x, int y);
	~Position();

	int getX() const;
	void setX(const int& x);

	int getY() const;
	void setY(const int& y);

	/*
	Pasa coordenadas a posición.
	*/
	void setPosition(int x, int y);

	/*
	Imprime la posición actual en la consola. (Debug)
	 */
	void printPosition() const;

	auto operator==(const Position& other) const
	{
		return (m_posX == other.m_posX && m_posY == other.m_posY);
	}

private:
	int m_posX;
	int m_posY;

};