#include "tile.h"

// Constructors and Destructor
Tile::Tile()
{
	m_type = TYPE_EMPTY;
	m_isRevealed = false;
}
Tile::~Tile()
{
}

// Getters and Setters
tileType Tile::getType() const
{
	return m_type;
}
void Tile::setType(const tileType& type)
{
	m_type = type;
}

Position Tile::getPosition() const
{
	return m_position;
}
void Tile::setPosition(const Position& position)
{
	m_position = position;
}

bool Tile::getIsRevealed() const
{
	return m_isRevealed;
}
void Tile::setIsRevealed(const bool& isRevealed)
{
	m_isRevealed = isRevealed;
}