#include "game.h"
#include "raylib.h"

void drawBoard(const Board& board) 
{
	
}

int returnMiddle(int screenRes, int textureRes, int numTiles) 
{
	return (screenRes - textureRes * numTiles) / 2;
}