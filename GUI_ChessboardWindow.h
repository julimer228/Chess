#ifndef GUI_CHESSBOARDWINDOW_H
#define GUI_CHESSBOARDWINDOW_H
#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include "GUI_Button.h"
#include "GUI_HelpForSDL.h"
#include "GUI_Chessboard.h"
#include "GUI_Window.h"


/*Struktura odpowiedzialna za okno z szachownic�*/
typedef struct guigamewindow_t
{
	SDL_Window* window;//okno SDL
	SDL_Renderer* renderer;//render
	GUI_Widget* chessboard_widget;//szachownica
	GUI_Widget* back_button_widget;//przycisk powrotu do menu g��wnego
	SDL_Texture* background;//Tekstura t�a
	Game* game;//Struktura zawieraj�ca wszystkie funkcje zwi�zane z gr�
	bool menu_save;//Informacja czy gra zosta�a zapisana
}GUI_ChessboardWindow;

GUI_Window* GUI_CreateChessboardWindow(SDL_Window* window_t, SDL_Renderer* renderer, Game* game);
void GUI_DrawChessboardWindow(GUI_Window* window);
void GUI_DestroyChessboardWindow(GUI_Window* window);
void GUI_HandleChessboardWindowEvent(GUI_Window* chessboardwindow, SDL_Event* event);
#endif
