/**@file*/
#ifndef GUI_GAME_H
#define GUI_GAME_H
#include "GUI_HelpForSDL.h"
#include "GUI_Chessboard.h"
#include "Game.h"

/**Struktura zawieraj�ca wszystkie elementy potrzebne do utworzenia gry z interfejsem graficznym*/
typedef struct guigame_t
{
	SDL_Window* window;///<Okno w kt�rym zostanie wy�wietlona gra
	SDL_Renderer* renderer;///<render
	Game* game;///<Logika gry
	SDL_Texture* background_tx;///<Tekstura t�a
	SDL_Rect chessboard_location;///<Miejsce w kt�rym ma znajdowa� si� szachownica
	GUI_Chessboard* guichessboard;///<Szachownica
}GUI_Game;


/**Funkcja tworz�ca struktur� gry z interfejsem graficznym w pami�ci komputera
@return utworzona struktura lub NULL je�li nie uda�o si� poprawnie utworzy� struktury*/
GUI_Game* CreateGUI_Game();

/**Funkcja rysuj�ca g��wne okno gry
@param guigame struktura gry*/
void GUI_DrawGameWindow(GUI_Game* guigame, SDL_Renderer * renderer);

/**Funkcja usuwaj�ca struktur� z pami�ci
@param guigame struktura do usuni�cia*/
void GUI_GameDestroy(GUI_Game* guigame);

/**Funkcja uruchamiaj�ca gr� z interfejsem graficznym*/
void GameRun();


#endif 

