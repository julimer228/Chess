#ifndef GUI_GAMEHANDLER_H
#define GUI_GAMEHANDLER_H
#include <stdlib.h>
#include "GUI_ChessboardWindow.h"
#include "GUI_MenuWindow.h"
#include "Game.h"
#include <stdbool.h>
//Typ definiuj¹cy rodzaje okien
typedef enum windowtype
{
	MENU_WINDOW, //okno menu start
	HELP_WINDOW, //okno pomocy
	GAME_WINDOW //okno gry
}GUI_WindowType;

//Struktura zawieraj¹ca wszystkie elementy gry z interfejsem graficznym
typedef struct guigame_t
{
	SDL_Renderer* renderer;//render
	SDL_Window* window;//okno
	GUI_Window* actual_window;//okno, które jest aktualnie wyœwietlane
	GUI_WindowType* previous_window;//rodzaj poprzednio wyœwietlonego okna
	bool stop;//informacja o tym czy wyst¹pi³y b³êdy lub gra zosta³a zakoñczona
	bool duringTheGame;//informacja o tym czy partia trwa
	Game* game;//logika gry
}GUI_Handler;

/*Funkcja alokujê strukturê odpowiadaj¹c¹ za graficzn¹ wersjê gry w pamiêci
@return wskaŸnik na nowo utworzon¹ grê*/
GUI_Handler* CreateHandler();

/*Usuwa strukturê z pamiêci
@param handler wskaŸnik na strukturê, która ma zostac usuniêta*/
void DestroyHandler(GUI_Handler* handler);

/*Funkcja odpowiedzialna za uruchomienie gry
@return true, jeœli gra zosta³a w³¹czona poprawnie w przeciwnym wypadku false*/
bool RunGraphicalGame();


#endif
#pragma once
