#include "visuals.h"

// Test main
int main() {

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
    int x, y;

    bool valid;

    // Select difficulty
	board = Board(easy); // Default to easy ,normal, hard, or custom


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLUE);

        //Draw all tiles
        for (int i = 0; i < board.getSizeX(); i++) 
        {
            for (int j = 0; j < board.getSizeY(); j++) 
            {
				// Dibujar el fondo de la casilla
				DrawTexture(flagTexture, returnMiddle(screenWidth, tileTexture.width, board.getSizeX()) + i * tileTexture.width, 
                            returnMiddle(screenHeight, tileTexture.height, board.getSizeY()) + j * tileTexture.height, RAYWHITE);

                if (board.getTile(i, j).getIsRevealed()) 
                {
                    
				}
            }
		}

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

//// True main (working on it)
//int main()
//{
//    // Obtener resolución de pantalla
//    int screenWidth = GetMonitorWidth(0);
//    int screenHeight = GetMonitorHeight(0);
//
//    // Crear ventana del tamaño de la pantalla
//    InitWindow(screenWidth, screenHeight, "Buscaminas adaptado a pantalla");
//
//    // Carga la textura (sprite)
//    Texture2D tileTexture = LoadTexture("./sprites/tile.png");
//    Texture2D mineTexture = LoadTexture("./sprites/mine.png");
//    Texture2D flagTexture = LoadTexture("./sprites/bandera.png");
//
//    SetTargetFPS(60);
//
//    while (!WindowShouldClose()) {
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        EndDrawing();
//    }
//
//    CloseWindow();
//    return 0;
//
//    return 0;
//}