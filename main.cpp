#include "raylib.h"
#include "game.h"

int returnMiddle(int screenRes, int textureRes, int numTiles)
{
    return (screenRes - textureRes * numTiles) / 2;
}

// Test main
int main() {

    //srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    // Obtener resolución de pantalla
    int screenWidth = 1500;
    int screenHeight = 800;

    // Crear ventana del tamaño de la pantalla
    InitWindow(screenWidth, screenHeight, "Buscaminas adaptado a pantalla");

    // Carga la textura (sprite)
    Texture2D tileTexture = LoadTexture("./sprites/tile.png");
    Texture2D mineTexture = LoadTexture("./sprites/mine.png");
    Texture2D flagTexture = LoadTexture("./sprites/flag.png");
    Texture2D zeroTexture = LoadTexture("./sprites/0.png");
    Texture2D oneTexture = LoadTexture("./sprites/1.png");
    Texture2D twoTexture = LoadTexture("./sprites/2.png");
    Texture2D threeTexture = LoadTexture("./sprites/3.png");
    Texture2D fourTexture = LoadTexture("./sprites/4.png");
    Texture2D fiveTexture = LoadTexture("./sprites/5.png");
    Texture2D sixTexture = LoadTexture("./sprites/6.png");
    Texture2D sevenTexture = LoadTexture("./sprites/7.png");
    Texture2D eightTexture = LoadTexture("./sprites/8.png");

    SetTargetFPS(60);

    // GAME 
    Board board;
    gameState state = playing;
    int x = 1;
    int y = 1;

    bool valid;

    // Select difficulty
    board = Board(easy); // Default to easy ,normal, hard, or custom


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);

        //Draw all tiles
        selectTile(x, y, board);
        board.initBoard(x, y);
        board.revealAdjacentTiles(x, y);

        for (int i = 0; i < board.getSizeX(); i++)
        {
            for (int j = 0; j < board.getSizeY(); j++)
            {
                // Dibujar el fondo de la casilla
                if (board.getTile(i, j).getIsFlagged())
                    DrawTexture (flagTexture, returnMiddle(screenWidth, tileTexture.width, board.getSizeX()) + i * tileTexture.width,
                                 returnMiddle(screenHeight, tileTexture.height, board.getSizeY()) + j * tileTexture.height, RAYWHITE);
                else if (board.getTile(i, j).getIsRevealed())
                {
                    if (board.getTile(i, j).getType() == TYPE_MINE)
                        DrawTexture(mineTexture, returnMiddle(screenWidth, tileTexture.width, board.getSizeX()) + i * tileTexture.width,
                                     returnMiddle(screenHeight, tileTexture.height, board.getSizeY()) + j * tileTexture.height, RAYWHITE);
                    else
                    {
                        // Draw the number of adjacent mines
                        int adjacentMines = board.getAdjacentMines(i, j);
                        Texture2D numberTexture;
                        switch (adjacentMines)
                        {
                            case 0: numberTexture = zeroTexture; break;
                            case 1: numberTexture = oneTexture; break;
                            case 2: numberTexture = twoTexture; break;
                            case 3: numberTexture = threeTexture; break;
                            case 4: numberTexture = fourTexture; break;
                            case 5: numberTexture = fiveTexture; break;
                            case 6: numberTexture = sixTexture; break;
                            case 7: numberTexture = sevenTexture; break;
                            case 8: numberTexture = eightTexture; break;
                        }
                        DrawTexture(numberTexture, returnMiddle(screenWidth, tileTexture.width, board.getSizeX()) + i * tileTexture.width,
                                     returnMiddle(screenHeight, tileTexture.height, board.getSizeY()) + j * tileTexture.height, RAYWHITE);
                    }
                }
                else
                {
                    // Dibujar el sprite de la casilla no revelada
                    DrawTexture(tileTexture, returnMiddle(screenWidth, tileTexture.width, board.getSizeX()) + i * tileTexture.width,
                                 returnMiddle(screenHeight, tileTexture.height, board.getSizeY()) + j * tileTexture.height, RAYWHITE);
				}
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


//int main() 
//{
//	// Initialize the game
//	mainGame();
//	
//	return 0;
//}