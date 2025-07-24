#include "position.h"

Position::Position()
{
	m_posX = 0;
	m_posY = 0;
}

Position::~Position()
{
}

Position::Position(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

int Position::getX() const
{
	return m_posX;
}
void Position::setX(const int& x)
{
	m_posX = x;
}
int Position::getY() const
{
	return m_posY;
}
void Position::setY(const int& y)
{
	m_posY = y;
}

void Position::setPosition(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Position::printPosition() const
{
	cout << "Position: (" << m_posX << ", " << m_posY << ")" << endl;
}