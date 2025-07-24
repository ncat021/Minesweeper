#include "position.h"

enum tileType
{
	TYPE_EMPTY,
	TYPE_MINE
};

class Tile
{
public:
	// Constructors
	Tile();
	~Tile();

	// Getters and Setters
	tileType getType() const;
	void setType(const tileType& type);

	Position getPosition() const;
	void setPosition(const Position& position);

	bool getIsRevealed() const;
	void setIsRevealed(const bool& isRevealed);

	bool getIsFlagged() const;
	void setIsFlagged(const bool& isFlagged);

private:
	Position m_position;
	tileType m_type;

	bool m_isRevealed;
	bool m_isFlagged;
};
