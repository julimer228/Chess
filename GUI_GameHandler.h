#ifndef GUI_GAMEHANDLER_H
#define GUI_GAMEHANDLER_H
#include <stdlib.h>
#include "GUI_ChessboardWindow.h"
#include "GUI_MenuWindow.h"
#include "Game.h"
#include <stdbool.h>
//Typ definiuj�cy rodzaje okien
typedef enum windowtype
{
	MENU_WINDOW, //okno menu start
	HELP_WINDOW, //okno pomocy
	GAME_WINDOW //okno gry
}GUI_WindowType;

//Struktura zawieraj�ca wszystkie elementy gry z interfejsem graficznym
typedef struct guigame_t
{
	SDL_Renderer* renderer;//render
	SDL_Window* window;//okno
	GUI_Window* actual_window;//okno, kt�re jest aktualnie wy�wietlane
	GUI_WindowType* previous_window;//rodzaj poprzednio wy�wietlonego okna
	bool stop;//informacja o tym czy wyst�pi�y b��dy lub gra zosta�a zako�czona
	bool duringTheGame;//informacja o tym czy partia trwa
	Game* game;//logika gry
}GUI_Handler;

/*Funkcja alokuj� struktur� odpowiadaj�c� za graficzn� wersj� gry w pami�ci
@return wska�nik na nowo utworzon� gr�*/
GUI_Handler* CreateHandler();

/*Usuwa struktur� z pami�ci
@param handler wska�nik na struktur�, kt�ra ma zostac usuni�ta*/
void DestroyHandler(GUI_Handler* handler);

/*Funkcja odpowiedzialna za uruchomienie gry
@return true, je�li gra zosta�a w��czona poprawnie w przeciwnym wypadku false*/
bool RunGraphicalGame();


#endif
#pragma once
