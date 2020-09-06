/**@file*/
#ifndef GUI_GAME_H
#define GUI_GAME_H
#include "GUI_HelpForSDL.h"
#include "GUI_Chessboard.h"
#include "Game.h"

/**Struktura zawieraj¹ca wszystkie elementy potrzebne do utworzenia gry z interfejsem graficznym*/
typedef struct guigame_t
{
	SDL_Window* window;///<Okno w którym zostanie wyœwietlona gra
	SDL_Renderer* renderer;///<render
	Game* game;///<Logika gry
	SDL_Texture* background_tx;///<Tekstura t³a
	SDL_Rect chessboard_location;///<Miejsce w którym ma znajdowaæ siê szachownica
	GUI_Chessboard* guichessboard;///<Szachownica
}GUI_Game;


/**Funkcja tworz¹ca strukturê gry z interfejsem graficznym w pamiêci komputera
@return utworzona struktura lub NULL jeœli nie uda³o siê poprawnie utworzyæ struktury*/
GUI_Game* CreateGUI_Game();

/**Funkcja rysuj¹ca g³ówne okno gry
@param guigame struktura gry*/
void GUI_DrawGameWindow(GUI_Game* guigame, SDL_Renderer * renderer);

/**Funkcja usuwaj¹ca strukturê z pamiêci
@param guigame struktura do usuniêcia*/
void GUI_GameDestroy(GUI_Game* guigame);

/**Funkcja uruchamiaj¹ca grê z interfejsem graficznym*/
void GameRun();


#endif 

